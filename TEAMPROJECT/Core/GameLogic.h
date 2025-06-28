#pragma once
#include "AsciiObject.h"
#include "../DH/Enums.h"
#include "../DH/Pos.h"
#include "../DH/Entity.h"
#include "../DH/Player.h"
#include "../DH/Enemy.h"
#include "../DH/Map.h"
#include "../DH/EnemyManager.h"
#include "../DH/PlayerManager.h"
#include "../DH/Scene.h"
#include <vector>

using std::vector;

// 매크로
//#define MAP_WIDTH 20
// 상수(const)

class GameScene : public Scene
{
public:
    Map map;
    PlayerManager PlayerManager;
    EnemyManager enemyManager;

private:
    vector<Entity*> entities;
    int maxDebugCnt = 4;
    int currDebugCnt = 0;

public:
    GameScene();

    void SceneInit(SCENE _type, vector<AsciiObject>* _asciiObjects) override;
    void Update() override;
private:
    void EntityInit();
    
    void EnemiesMove();
    void EntityUpdate();
    void HandleInput();

    void Render();
    void RenderUI();
    void RenderEffect();
};