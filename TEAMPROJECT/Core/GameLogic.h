#pragma once
#include "../DH/Enums.h"
#include "AsciiObject.h"
#include "../DH/Entity.h"
#include "../DH/Player.h"
#include "../DH/Enemy.h"
#include "../DH/Map.h"
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

    Player _player;
    vector<Enemy> _enemies;
    Map _gameMap;

    int _maxFollowingEnemyCnt;
public:
    GameLogic();

    void Initialized(
        vector<AsciiObject>* objs,
        int maxFollowingEnemy
    );
    void Update();
    void InfoScene();
	void InfoSceneInit();
private:
    void LoadStage();
    void EntityInit();
	void ItemInit();
    
    void EnemiesMove();
    void HandleInput();

    void Render();
    void RenderUI();
    void GameScene();
    void RenderInfo();
    void RenderEffect();
};