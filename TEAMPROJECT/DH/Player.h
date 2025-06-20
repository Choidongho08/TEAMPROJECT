#pragma once
#include <math.h>
#include "../Core/KeyController.h"
#include "Entity.h"
#include "Enemy.h"
#include "Map.h"

class PlayerState : public EntityState
{
public:
    int score;
    bool isHaveSkill;
    Skill whatSkill;
};

class Player : public Entity
{
public:
    PlayerState _state;
    Skill _skill;

private:

public:
    Player();
    Player(PlayerState playerState, ENTITYPOS playerPos);

    void Initialize(
        int mapHeight,
        int mapWidth,
        Map* gameMap
    );
    void Update();
    void HandleInput(Map& gameMap);
    void SetSkill(Skill skill);
    void UseSkill(std::vector<std::vector<char>>* pGameMap, Skill skillEnum, Enemy* pEnemy);
    
private:
    void Move();
};