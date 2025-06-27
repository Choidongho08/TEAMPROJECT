#pragma once
#include <vector>
#include <string>

#include "Pos.h"
#include "Enums.h"
#include "Map.h"

// 위치 관련 구조체
typedef struct _TagEntityPos
{
    POS tPos;     // 현재 위치
    POS tNewPos;    // 다음 위치
    POS tStartPos; // 시작 위치
    POS tForward;
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
    Direction dir;
    ENTITY_TYPE type;

    Entity(ENTITYPOS _entityPos, EntityState _entityState, ENTITY_TYPE _type, Map* _map);

    void Rotate(Direction _direction);
    void Rotate90();
    void Rotate180();
    void RotationMove();
    void Render(std::string _s);
    void Move(Map* _map);

protected:
    Map* map = nullptr;
};

