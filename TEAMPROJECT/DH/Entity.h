#pragma once
#include "Enums.h"
#include <vector>

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

class Entity
{
public:
    ENTITYPOS pos;
    EntityState state;
};

