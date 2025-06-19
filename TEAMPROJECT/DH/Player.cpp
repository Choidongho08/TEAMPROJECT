#include "Player.h"

Player::Player() : Entity({{0,0}, {0,0}, {0,0}}, {true})
{
    _state = { false };
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
    int mapHeight,
    int mapWidth,
    std::vector<std::vector<char>>* pGameMap
)
{
    for (int i = 0; i < mapHeight; ++i)
    {
        for (int j = 0; j < mapWidth; ++j)
        {
            if ((*pGameMap)[i][j] == (char)Tile::PLAYER_START)
                _pos.tStartPos = { j, i };
        }
    }
    _pos.tPos = _pos.tStartPos;
    _state = { true, false, false, false, false };
}

void Player::Update()
{

}

void Player::Move(POS nextPos)
{
    _pos.tNewPos = nextPos;
    _forward = nextPos - _pos.tPos;
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
