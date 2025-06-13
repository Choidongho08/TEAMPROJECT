#pragma once
#include "Map.h"
#include "Enums.h"
#include "AsciiObject.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

using std::vector;

// 매크로
//#define MAP_WIDTH 20
// 상수(const)

void Init(AsciiObjcets& objs, char gameMap
    [MAP_HEIGHT][MAP_WIDTH], Player* pPlayer);
void PlayerInit(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer);
void EnemyInit(char gameMap[MAP_HEIGHT][MAP_WIDTH], vector<Enemy>* pEnemies);
void LoadStage(char gameMap[MAP_HEIGHT][MAP_WIDTH]);

void Update(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer, Scene& eCurScene);
void HandleInput(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer);

void Render(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer, vector<Enemy>* pEnemies);
void RenderUI(Player* pPlayer);
void GameScene(Scene& eCurScene, char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer, vector<Enemy>* pEnemies);
void InfoScene(Scene& eCurScene);
void RenderInfo();
void RenderEffect();