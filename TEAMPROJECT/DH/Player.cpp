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

void Player::Move(POS nextPos)
{
    _pos.tNewPos = nextPos;
    _forward = nextPos - _pos.tPos;
}

void Player::SetSkill(Skill skill)
{
    _skill = skill;
}

void Player::UseSkill(char gameMap[MAP_HEIGHT][MAP_WIDTH], Skill skillEnum, Enemy* pEnemy)
{
    if (!_state.isHaveSkill) return;

    if (skillEnum == Skill::KILL)
    {
        if (_forward == (*pEnemy)._pos.tPos)
        {
            (*pEnemy)._state._isAlive = false;
        }
        _state.isHaveSkill = false;
    }
    else if (skillEnum == Skill::SIGHT)
    {
        if (_forward == (*pEnemy)._pos.tPos)
        {
            (*pEnemy)._state._isAlive = false;
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
            if (gameMap[dashEndPos.x][dashEndPos.y] == (char)Tile::WALL)
                break;

            num++;
        }
        _pos.tNewPos = dashEndPos;
    }
}
