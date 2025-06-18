#pragma once
#include "Map.h"
#include "Entity.h"
#include "Enemy.h"

class PlayerState : public EntityState
{
public:
    bool isHaveSkill;
    bool isKillEnemy;
    bool isSightLight;
    bool isDash;
};

class Player : public Entity
{
public:
    PlayerState _state;
    POS _forward;
    Skill _skill;

    Player();
    Player(PlayerState playerState, ENTITYPOS playerPos);

    void Move(POS nextPos);
    void SetSkill(Skill skill);
    void UseSkill(char gameMap[MAP_HEIGHT][MAP_WIDTH], Skill skillEnum, Enemy* pEnemy);
};