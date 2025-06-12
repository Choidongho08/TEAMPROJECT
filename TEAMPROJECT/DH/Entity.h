#pragma once
#include "Enums.h"
#include<vector>

typedef struct _pos
{
    int x;
    int y;

    bool operator == (const _pos& other) const
    {
        return (x == other.x && y == other.y);
    }
    POS operator - (const _pos& other) const
    {
        return POS(x - other.x, y - other.y);
    }
    POS operator * (const int& num) const
    {
        return POS(x * num, y * num);
    }
}POS, * PPOS;

// 위치 관련 구조체
typedef struct _TagEntityPos
{
    POS tPos;     // 현재 위치
    POS tNewPos;    // 다음 위치
    POS tStartPos; // 시작 위치
} ENTITYPOS, * PENTITYPOS;

class EntityState
{
public:
    bool isAlive;
};

class PlayerState : public EntityState
{
public: 
    bool isHaveSkill;
    bool isKillEnemy;
    bool isSightLight;
    bool isDash;
};

class Entity
{
public:
    ENTITYPOS pos;
    EntityState state;
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

class Enemy : public Entity
{
};