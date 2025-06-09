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

// ��ġ ���� ����ü
typedef struct _TagEntityPos
{
    POS tPos;     // ���� ��ġ
    POS tNewPos;    // ���� ��ġ
    POS tStartPos; // ���� ��ġ
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