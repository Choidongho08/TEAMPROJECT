#pragma once
#include "Enums.h"
#include "AsciiObject.h"
#include <vector>

using std::vector;

// ��ũ��
//#define MAP_WIDTH 20
// ���(const)
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

// ��ġ ���� ����ü
typedef struct _tagplayerpos
{
    POS tPos;     // ���� ��ġ
    POS tNewPos;    // ���� ��ġ
    POS tStartPos; // ���� ��ġ
    POS tEndPos;   // ��ǥ ��ġ
} PLAYERPOS, * PPLAYERPOS;

// ���� ���� ����ü
typedef struct _tagplayerstate
{
    int bombcnt;    // ��ź ����
    int bombpower;  // ��ź �Ŀ�
    bool isWallPush;  // �� �б� ����
    bool isPushOnOff; // ����ġ ����
    bool isTrans;     // ������ ����
} PLAYERSTATE, * PPLAYERSTATE;

// ���� �÷��̾� ����ü
typedef struct _tagPlayer
{
    PLAYERPOS position;    // ��ġ ����
    PLAYERSTATE state;     // ���� ����
} PLAYER, * PPLAYER;

typedef struct _tagBoom
{
    POS tPos;
    int life;
    bool isDie;
    vector<POS> vecEffect; // ���� ����Ʈ
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