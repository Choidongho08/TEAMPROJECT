#pragma once
#include "Entity.h"
#include "Enemy.h"

class PlayerState : public EntityState
{
public:
    bool isHaveSkill;
    bool isKillEnemy;
    bool isSightLight;
    bool isDash;
};

class Player : public Entity
{
public:
    PlayerState state;
    POS forwardPos;
    Skill skill;

    void UseSkill(char gameMap[MAP_HEIGHT][MAP_WIDTH], Skill skillEnum, Enemy* pEnemy)
    {
        if (!state.isHaveSkill) return;

        forwardPos = pos.tNewPos - pos.tPos;

        if (skillEnum == Skill::KILL)
        {
            if (forwardPos == (*pEnemy).pos.tPos)
            {
                (*pEnemy).state.isAlive = false;
            }
            state.isHaveSkill = false;
        }
        else if (skillEnum == Skill::SIGHT)
        {
            if (forwardPos == (*pEnemy).pos.tPos)
            {
                (*pEnemy).state.isAlive = false;
            }
            state.isHaveSkill = false;
        }
        else if (skillEnum == Skill::DASH)
        {
            POS dashEndPos{ 0,0 };
            int num = 1;
            while (true)
            {
                dashEndPos = forwardPos * num;
                if (gameMap[dashEndPos.x][dashEndPos.y] == (char)Tile::WALL)
                    break;

                num++;
            }
            pos.tNewPos = dashEndPos;
        }
    }
};