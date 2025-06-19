#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "Map.h"

class PlayerState : public EntityState
{
public:
    bool isHaveSkill;
    Skill whatSkill;
};

class Player : public Entity
{
public:
    PlayerState _state;
    POS _forward;
    Skill _skill;

    Player();
    Player(PlayerState playerState, ENTITYPOS playerPos);

    void Initialize(
        int mapHeight,
        int mapWidth,
        Map* gameMap
    );
    void Update();
    void Move(POS nextPos);
    void SetSkill(Skill skill);
    void UseSkill(std::vector<std::vector<char>>* pGameMap, Skill skillEnum, Enemy* pEnemy);
};