#pragma once
#include <math.h>
#include <functional>
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
    bool isUsingSkill;
    Skill usingSkill;
};

class Player : public Entity
{
public:
    PlayerState state;
    Skill skill;

private:
    int mapHeight;
    int mapWidth;
    double skillStartTime;
    double skillMaxTime;

public:
    Player();
    Player(PlayerState playerState, ENTITYPOS playerPos);

    void Initialize(
        int _mapHeight,
        int _mapWidth
    );
    void Update(const Map& _map);
    void SetSkill(Skill skill);
    bool UseSkill();
    void CheckTile(Map* _map);
    void SetSight(int sight);
    void SetSightTime(float time);
    
private:
};