#include "Player.h"

Player::Player() : Entity({{0,0}, {0,0}, {0,0}}, {true})
{
    _state = { 0, false, (int)Skill::None };
    _forward = { 0,0 };
    _skill = Skill::None;
}

Player::Player(PlayerState playerState, ENTITYPOS playerPos) : Entity(playerPos, playerState)
{
    _state = playerState;
    _forward = { 0,0 };
    _skill = Skill::None;
}

void Player::Initialize(
    int mapWidth,
    int mapHeight,
    Map* gameMap
)
{
    for (int i = 0; i < mapHeight; ++i)
    {
        for (int j = 0; j < mapWidth; ++j)
        {
            if ((*gameMap).isTile(j, i, Tile::PLAYER_START))
                _pos.tStartPos = { j, i };
        }
    }
    _pos.tPos = _pos.tStartPos;
    _state = { 0, false, (int)Skill::None};
}

void Player::Update()
{

}

void Player::Move()
{
    _pos.tPos = _pos.tNewPos;
    _forward = _pos.tNewPos - _pos.tPos;
}

void Player::HandleInput(Map& gameMap)
{
    _pos.tNewPos = _pos.tPos;
    Key eKey = KeyController();
    switch (eKey)
    {
    case Key::UP:
        --_pos.tNewPos.y;
        break;
    case Key::DOWN:
        ++_pos.tNewPos.y;
        break;
    case Key::LEFT:
        --_pos.tNewPos.x;
        break;
    case Key::RIGHT:
        ++_pos.tNewPos.x;
        break;
    case Key::SPACE: // 스킬
        //SpawnBomb(gameMap, pPlayer, vecBomb);
        break;
    }
    // clamp함수는 c++17에 나옴
    _pos.tNewPos.x = std::clamp(_pos.tNewPos.x, 0, gameMap.GetMapCol());
    _pos.tNewPos.y = std::clamp(_pos.tNewPos.y, 0, gameMap.GetMapRow());

    _forward = _pos.tNewPos - _pos.tPos;

    if (!gameMap.isTile(_pos.tNewPos.x, _pos.tNewPos.y, Tile::WALL))
        Move();
}

void Player::SetSkill(Skill skill)
{
    _skill = skill;
}

void Player::UseSkill(std::vector<std::vector<char>>* pGameMap, Skill skillEnum, Enemy* enemy)
{
    if (!_state.isHaveSkill) return;

    if (skillEnum == Skill::KILL)
    {
        if (_forward == (*enemy)._pos.tPos)
        {
            (*enemy)._state._isAlive = false;
        }
        _state.isHaveSkill = false;
    }
    else if (skillEnum == Skill::SIGHT)
    {
        if (_forward == (*enemy)._pos.tPos)
        {
            (*enemy)._state._isAlive = false;
        }
        _state.isHaveSkill = false;
    }
    else if (skillEnum == Skill::DASH)
    {
        POS dashEndPos{ 0,0 };
        int num = 1;
        while (true)
        {
            dashEndPos = _forward * num;
            if ((*pGameMap)[dashEndPos.x][dashEndPos.y] == (char)Tile::WALL)
                break;

            num++;
        }
        _pos.tNewPos = dashEndPos;
    }
}
