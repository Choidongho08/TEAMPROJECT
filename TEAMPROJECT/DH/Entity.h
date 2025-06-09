#pragma once
#include<vector>

typedef struct _pos
{
    int x;
    int y;

    bool operator == (const _pos& other) const
    {
        return (x == other.x && y == other.y);
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
};

class Enemy : public Entity
{
};