#pragma once
#include "Enums.h"
#include "AsciiObject.h"
#include <vector>

using std::vector;

// 매크로
//#define MAP_WIDTH 20
// 상수(const)
const int MAP_WIDTH = 21;
const int MAP_HEIGHT = 20;

typedef struct _pos
{
	int x;
	int y;

    bool operator == (const _pos& other) const
    {
        return (x == other.x && y == other.y);
    }
}POS, *PPOS;

// 위치 관련 구조체
typedef struct _tagplayerpos
{
    POS tPos;     // 현재 위치
    POS tNewPos;    // 다음 위치
    POS tStartPos; // 시작 위치
    POS tEndPos;   // 목표 위치
} PLAYERPOS, * PPLAYERPOS;

// 상태 관련 구조체
typedef struct _tagplayerstate
{
    int bombcnt;    // 폭탄 개수
    int bombpower;  // 폭탄 파워
    bool isWallPush;  // 벽 밀기 여부
    bool isPushOnOff; // 스위치 상태
    bool isTrans;     // 슬라임 상태
} PLAYERSTATE, * PPLAYERSTATE;

// 최종 플레이어 구조체
typedef struct _tagPlayer
{
    PLAYERPOS position;    // 위치 정보
    PLAYERSTATE state;     // 상태 정보
} PLAYER, * PPLAYER;

typedef struct _tagBoom
{
    POS tPos;
    int life;
    bool isDie;
    vector<POS> vecEffect; // 폭발 이펙트
}BOMB, * PBOMB;

void Init(AsciiObjcets& objs, char gameMap
    [MAP_HEIGHT][MAP_WIDTH], PPLAYER pPlayer);
void PlayerInit(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    PPLAYER pPlayer);
void LoadStage(char gameMap[MAP_HEIGHT][MAP_WIDTH]);

void Update(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    PPLAYER pPlayer, Scene& eCurScene, vector<BOMB>& vecBomb);
void HandleInput(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    PPLAYER pPlayer, vector<BOMB>& vecBomb);

void SpawnBomb(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    PPLAYER pPlayer, vector<BOMB>& vecBomb);
void UpdateBomb(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    PPLAYER pPlayer, vector<BOMB>& vecBomb);
void ExplosionBomb(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    PPLAYER pPlayer, POS bombPos, vector<POS>& vecEffect);
void RemoveDeadBomb(vector<BOMB>& vecBomb);

void Render(char gameMap[MAP_HEIGHT][MAP_WIDTH],
    PPLAYER pPlayer, vector<BOMB>& vecBomb);
void RenderUI(PPLAYER pPlayer);
void GameScene(Scene& eCurScene, char gameMap[MAP_HEIGHT][MAP_WIDTH],
    PPLAYER pPlayer, vector<BOMB>& vecBomb);
void InfoScene(Scene& eCurScene);
void RenderInfo();
void RenderEffect(vector<BOMB>& vecBomb);