#pragma once
#include "../DH/Enums.h"
#include "AsciiObject.h"
#include "../DH/Entity.h"
#include "../DH/Player.h"
#include "../DH/Enemy.h"
#include <vector>

using std::vector;

// 매크로
//#define MAP_WIDTH 20
// 상수(const)

class GameLogic
{
public:

private:
    vector<AsciiObject>* _pObjs;
    std::vector<std::vector<char>>* _pGameMap;

    Player _player;
    vector<Enemy> _enemies;

    int MAP_HEIGHT;
    int MAP_WIDTH;
    int maxFollowingEnemyCnt;
public:
    GameLogic();

    void Initialized(
        vector<AsciiObject>* objs,
        std::vector<std::vector<char>>* gameMap,
        int maxFollowingEnemy
    );
    void Update();
private:
    void PlayerInit();
    void EnemyInit();
    void LoadStage();
    
    void HandleInput();

    void Render();
    void RenderUI();
    void GameScene();
    void InfoScene();
    void RenderInfo();
    void RenderEffect();
};