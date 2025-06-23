#pragma once
#include <vector>
#include <string>

#include "Pos.h"
#include "Enums.h"
#include "Map.h"

// ��ġ ���� ����ü
typedef struct _TagEntityPos
{
    POS tPos;     // ���� ��ġ
    POS tNewPos;    // ���� ��ġ
    POS tStartPos; // ���� ��ġ
    POS tForward;
} ENTITYPOS, * PENTITYPOS;

class EntityState
{
public:
    bool _isAlive;
};

class Entity
{
public:
    ENTITYPOS pos;
    EntityState state;
    Direction dir;
    ENTITY_TYPE type;

    Entity(ENTITYPOS _entityPos, EntityState _entityState, ENTITY_TYPE _type);

    void Rotate(Direction _direction);
    void RotationMove();
    void Render(std::string _s);
    void Move(Map* _map);
};

