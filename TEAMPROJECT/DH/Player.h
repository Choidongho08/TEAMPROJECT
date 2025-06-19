#pragma once
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
    PlayerState _state
    POS _forward;
    Skill _skill;

    Player();
    Player(PlayerState playerState, ENTITYPOS playerPos);

    void Initialize(
        int mapHeight,
        int mapWidth,
        std::vector<std::vector<char>>* pGameMap
    );
    void Update();
    void Move(POS nextPos);
    void SetSkill(Skill skill);
    void UseSkill(std::vector<std::vector<char>>* pGameMap, Skill skillEnum, Enemy* pEnemy);
};