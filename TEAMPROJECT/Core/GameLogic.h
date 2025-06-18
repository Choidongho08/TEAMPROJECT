#pragma once
#include "../DH/Map.h"
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
    vector<AsciiObject>* objs;
    char** gameMap;
    Scene* pCurScene;

    Player player;
    vector<Enemy> enemies;

public:
    GameLogic(
        vector<AsciiObject>* objs,
        char** gameMap,
        Scene *curScene
        )
        : objs(objs), gameMap(gameMap), pCurScene(curScene)
    {
        
    }

    void Initialized();
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