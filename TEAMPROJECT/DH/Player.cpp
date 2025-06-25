#include "Player.h"

Player::Player() : Entity({{0,0}, {0,0}, {0,0}}, {true}, ENTITY_TYPE::Player)
{
    state = { 0, false, (int)Skill::None };
    pos = { 0 };
    skill = Skill::None;
}

Player::Player(PlayerState _state, ENTITYPOS _pos) : Entity(_pos, _state, ENTITY_TYPE::Player)
{
    state = _state;
    pos = _pos;
    pos.tForward = { 0,0 };
    skill = Skill::None;
}

void Player::Initialize(
    int _mapWidth,
    int _mapHeight
)
{
}

void Player::Update()
{

}

void Player::Move(Map* _map)
{
    Entity::Move(_map);

    pos.tForward = pos.tNewPos - pos.tPos;
}

void Player::CheckTile(Map* _map)
{
    if (_map->isTile(pos.tPos.x, pos.tPos.y, Tile::COIN))
    {
        state.score++;
        _map->SetMapTile(pos.tPos.x, pos.tPos.y, Tile::ROAD);
    }
    if (_map->isTile(pos.tPos.x, pos.tPos.y, Tile::ITEM))
    {
        state.isHaveSkill = true;
        srand((unsigned int)time(nullptr));
        int rVal = rand() % (int)Skill::END;
        state.whatSkill = (Skill)rVal;
        _map->SetMapTile(pos.tPos.x, pos.tPos.y, Tile::ROAD);
    }
}

void Player::SetSkill(Skill skill)
{
    skill = skill;
}

void Player::UseSkill(Map* _pGameMap, Skill _skillEnum)
{
    if (!state.isHaveSkill) return;

    if (_skillEnum == Skill::KILL)
    {
        state.isHaveSkill = false;
    }
    else if (_skillEnum == Skill::SIGHT)
    {
        state.isHaveSkill = false;
    }
    else if (_skillEnum == Skill::DASH)
    {
        POS dashEndPos{ 0,0 };
        int num = 1;
        while (true)
        {
            dashEndPos = pos.tForward * num;
            if (_pGameMap->isTile(dashEndPos.x, dashEndPos.y, Tile::WALL))
            {
                dashEndPos = dashEndPos - pos.tForward;
                break;
            }

            num++;
        }
        pos.tNewPos = dashEndPos;
    }
}
