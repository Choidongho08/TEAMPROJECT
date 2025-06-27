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
    Skill haveSkill;
    bool isUsingSkill;
    Skill usingSkill;
};

class Player : public Entity
{
public:
    PlayerState state;

private:
    int mapHeight;
    int mapWidth;

    // ���� ��ų ����
    double skillStartTime;
    double skillMaxTime;
    
    // �뽬 ��ų ����
    POS dashEndPos;
    int dashCnt;

public:
    // ų ��ų ����
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
    void SetSkill(Skill skill);
    void UseSkill();
    void CheckTile();
    void SetSight(int sight);
    void SetSkillTime(float time);
    void KillEnemy(const POS& killPos);
    
private:
};