#pragma once
#include <math.h>
#include "../Core/KeyController.h"
#include "Entity.h"
#include "Map.h"

class PlayerState : public EntityState
{
public:
    int score;
    int maxSight;
    bool isHaveSkill;
    Skill whatSkill;
};

class Player : public Entity
{
public:
    PlayerState state;
    Skill skill;

private:
    int mapHeight;
    int mapWidth;

public:
    Player();
    Player(PlayerState playerState, ENTITYPOS playerPos);

    void Initialize(
        int _mapHeight,
        int _mapWidth
    );
    void Update();
    void SetSkill(Skill skill);
    void UseSkill(Map* _pGameMap);
    void CheckTile(Map* _map);
    void SetSight(int sight);
    
private:
};