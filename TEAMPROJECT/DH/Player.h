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
    int curSight;
    bool isHaveSkill;
    SKILL haveSkill;
    bool isUsingSkill;
    SKILL usingSkill;
};

class Player : public Entity
{
public:
    PlayerState state;

private:
    int mapHeight;
    int mapWidth;

    // 공통 스킬 변수
    double skillStartTime;
    double skillMaxTime;
    
    // 대쉬 스킬 변수
    POS dashEndPos;

public:
    // 킬 스킬 변수
    std::function<void(POS)> OnKillEnemy;
private:

public:
    Player();
    Player(PlayerState playerState, ENTITYPOS playerPos, Map* _map);

    void Initialize(
        int _mapHeight,
        int _mapWidth
    );
    void Update();
    void SetSkill(SKILL skill);
    void UseSkill();
    void CheckTile();
    void SetSight(int sight);
    void SetSkillTime(float time);
    void KillEnemy(const POS& killPos);
    
private:
};