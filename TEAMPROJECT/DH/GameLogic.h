#pragma once
#include "Enums.h"
#include "AsciiObject.h"
#include "Entity.h"
#include <vector>

using std::vector;

// 매크로
//#define MAP_WIDTH 20
// 상수(const)
const int MAP_WIDTH = 21;
const int MAP_HEIGHT = 20;

void Init(AsciiObjcets& objs, char gameMap
    [MAP_HEIGHT][MAP_WIDTH], Player* pPlayer);
void PlayerInit(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer);
void LoadStage(char gameMap[MAP_HEIGHT][MAP_WIDTH]);

void Update(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer, Scene& eCurScene);
void HandleInput(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer);

void Render(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer, Enemy* pEnemy);
void RenderUI(Player* pPlayer);
void GameScene(Scene& eCurScene, char gameMap[MAP_HEIGHT][MAP_WIDTH],
    Player* pPlayer);
void InfoScene(Scene& eCurScene);
void RenderInfo();
void RenderEffect();