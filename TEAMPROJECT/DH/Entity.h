#pragma once
#include <vector>
#include "Enums.h"

typedef struct _pos
{
    int x;
    int y;

    bool operator == (const _pos& other) const
    {
        return (x == other.x && y == other.y);
    }
    _pos operator - (const _pos& other) const
    {
        return _pos(x - other.x, y - other.y);
    }
    _pos operator * (const int& num) const
    {
        return _pos(x * num, y * num);
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
    bool _isAlive;
};

class Entity
{
public:
    ENTITYPOS _pos;
    EntityState _state;

    Entity(ENTITYPOS entityPos, EntityState entityState);
    ~Entity();
};

