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
    Map Map;
    EnemyManager EnemyManager;
    PlayerManager PlayerManager;
  

private:
    vector<AsciiObject>* pObjs;
    vector<Entity*> entities;
    int maxDebugCnt = 4;
    int currDebugCnt = 0;

    int maxFollowingEnemyCnt;
public:
    GameScene();

    void Initialized(
        vector<AsciiObject>* _objs,
        int _maxFollowingEnemy
    );
    void Update() override;
    void DeadSceneInit();
private:
    void LoadStage();
    void EntityInit();
	void ItemInit();
    
    void EntitiesMove();
    void HandleInput();

    void Render();
    void RenderUI();
    void RenderEffect();
};