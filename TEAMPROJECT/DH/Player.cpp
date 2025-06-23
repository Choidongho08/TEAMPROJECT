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

void Player::Move()
{
    pos.tPos = pos.tNewPos;
    pos.tForward = pos.tNewPos - pos.tPos;
}

void Player::SetSkill(Skill skill)
{
    skill = skill;
}

void Player::UseSkill(std::vector<std::vector<char>>* pGameMap, Skill skillEnum, Enemy* enemy)
{
    if (!state.isHaveSkill) return;

    if (skillEnum == Skill::KILL)
    {
        if (pos.tForward == (*enemy).pos.tPos)
        {
            (*enemy)._state._isAlive = false;
        }
        state.isHaveSkill = false;
    }
    else if (skillEnum == Skill::SIGHT)
    {
        if (pos.tForward == (*enemy).pos.tPos)
        {
            (*enemy)._state._isAlive = false;
        }
        state.isHaveSkill = false;
    }
    else if (skillEnum == Skill::DASH)
    {
        POS dashEndPos{ 0,0 };
        int num = 1;
        while (true)
        {
            dashEndPos = pos.tForward * num;
            if ((*pGameMap)[dashEndPos.x][dashEndPos.y] == (char)Tile::WALL)
                break;

            num++;
        }
        pos.tNewPos = dashEndPos;
    }
}
