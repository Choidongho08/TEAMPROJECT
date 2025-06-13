#include "GameLogic.h"
#include "../Core/Core.h"
#include "../Core/Console.h"
#include "../Core/Mci.h"
#include "TitleScene.h"
#include "KeyController.h"
#include <algorithm>
#include <fstream>

void Init(AsciiObjcets& objs, char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer)
{
	SetConsoleFont(L"NSimSun", {20, 20}, FW_BOLD);

	// ���� �ʱ�ȭ
	if (!InitAllSounds()) return;

	PlaySoundID(SOUNDID::BGM, true);

	// �ܼ�â ���� �ʱ�ȭ
	SetConsoleSettings(800, 600, false, L"HackMan");
	SetCursorVisual(true, 50);
	ObjectInit(objs);
	LoadStage(gameMap);
	PlayerInit(gameMap, pPlayer);
}

void LoadStage(char gameMap[MAP_HEIGHT][MAP_WIDTH])
{
	// �� ����
	// 1. ���� 2. �ܺ�
	// 1. ���δ� cpp���Ͽ� ��
	// strcpy_s(gameMap[0],	"21111111100000000000");
	// strcpy_s(gameMap[1],	"00000000111110000000");
	// strcpy_s(gameMap[2],	"00000000100010000000");
	// strcpy_s(gameMap[3],	"00111111100010000000");
	// strcpy_s(gameMap[4],	"00000000000011111000");
	// strcpy_s(gameMap[5],	"00000000000000001000");
	// strcpy_s(gameMap[6],	"00000001111111111000");
	// strcpy_s(gameMap[7],	"00000001000010000000");
	// strcpy_s(gameMap[8],	"00000001000011110000");
	// strcpy_s(gameMap[9],	"00011111000000010000");
	// strcpy_s(gameMap[10],	"00010000000000010000");
	// strcpy_s(gameMap[11],	"00011111111111000000");
	// strcpy_s(gameMap[12],	"00000000000001000000");
	// strcpy_s(gameMap[13],	"00111100000001000000");
	// strcpy_s(gameMap[14],	"00100100000001000000");
	// strcpy_s(gameMap[15],	"00100111111111000000");
	// strcpy_s(gameMap[16],	"00100000000001000000");
	// strcpy_s(gameMap[17],	"00100000000001000000");
	// strcpy_s(gameMap[18],	"00100000111111000000");
	// strcpy_s(gameMap[19],	"00300000000000000000");

	// 2. �ܺδ� txt���Ϸ�
	std::ifstream mapFile("Stage.txt");
	if (mapFile.is_open())
	{
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			// mapFile.getline(gameMap[i], MAP_WIDTH);
			mapFile >> gameMap[i];
		}
		mapFile.close();
		return;
	}
	else
		cout << "�� ���� �ʱ�ȭ ����" << endl;
	
}

void PlayerInit(char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer)
{
	// �� �����Ϳ� ���ؼ� �÷��̾� ��ġ ����
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (gameMap[i][j] == (char)Tile::PLAYER_START)
				(*pPlayer).pos.tStartPos = { j, i };
		}
	}
	pPlayer->pos.tPos = pPlayer->pos.tStartPos;
	pPlayer->state = { true, false, false, false, false };
}

void EnemyInit(char gameMap[MAP_HEIGHT][MAP_WIDTH], vector<Enemy>* pEnemies)
{
	for (auto pEnemy : (*pEnemies))
	{
		// �� �����Ϳ� ���ؼ� �÷��̾� ��ġ ����
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			for (int j = 0; j < MAP_WIDTH; ++j)
			{
				if (gameMap[i][j] == (char)Tile::ENEMY_START)
					pEnemy.pos.tStartPos = { j, i };
			}
		}
		pEnemy.pos.tPos = pEnemy.pos.tStartPos;
		pEnemy.state = { false };
	}
}

void Update(char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer, Scene& eCurScene)
{
	HandleInput(gameMap, pPlayer);
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		return;

	// if (pPlayer->pos.tPos == pPlayer->pos.tEndPos)
	// {
	// 	// PlaySound();
	// 	eCurScene = Scene::QUIT;
	// }
}

void HandleInput(char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer)
{
	pPlayer->pos.tNewPos = pPlayer->pos.tPos;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::UP:
		--pPlayer->pos.tNewPos.y;
		break;
	case Key::DOWN:
		++pPlayer->pos.tNewPos.y;
		break;
	case Key::LEFT:
		--pPlayer->pos.tNewPos.x;
		break;
	case Key::RIGHT:
		++pPlayer->pos.tNewPos.x;
		break;
	case Key::SPACE: // ��ų
		//SpawnBomb(gameMap, pPlayer, vecBomb);
		break;
	}
	// clamp�Լ��� c++17�� ����
	pPlayer->pos.tNewPos.x = std::clamp(pPlayer->pos.tNewPos.x, 0,  MAP_WIDTH - 2);
	pPlayer->pos.tNewPos.y = std::clamp(pPlayer->pos.tNewPos.y, 0,  MAP_HEIGHT - 1);

	if (gameMap[pPlayer->pos.tNewPos.y][pPlayer->pos.tNewPos.x] != (char)Tile::WALL)
		pPlayer->pos.tPos = pPlayer->pos.tNewPos;
}

void SpawnBomb(char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer)
{
	// if (pPlayer->state.bombcnt >= 5)
	// 	return;
	// 
	// const POS& playerPos = pPlayer->pos.tPos;
	// if (gameMap[playerPos.y][playerPos.x] == (char)Tile::ROAD)
	// {
	// 	gameMap[playerPos.y][playerPos.x] = (char)Tile::BOMB;
	// 	vecBomb.push_back(BOMB{playerPos.x, playerPos.y, 50, false});
	// 	++pPlayer->state.bombcnt;
	// }
}

void UpdateBomb(char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer)
{
	// // ������ ���̰� �����Ÿ��ٰ� ������
	// const int bombFlashInterval = 5;
	// const int bombLifeCycle = 10;
	// for (auto& bomb : vecBomb)
	// {
	// 	if (bomb.isDie)
	// 		continue;
	// 
	// 	--bomb.life;
	// 	
	// 	gameMap[bomb.tPos.y][bomb.tPos.x] = (bomb.life % bombLifeCycle >= bombFlashInterval) ? (char)Tile::BOMB : (char)Tile::FLASH_BOMB;
	// 	
	// 	if (bomb.life <= 0)
	// 	{
	// 		bomb.isDie = true;
	// 		--pPlayer->state.bombcnt;
	// 		// ������
	// 		ExplosionBomb(gameMap, pPlayer, bomb.tPos, bomb.vecEffect);
	// 	}
	// }
}

void ExplosionBomb(char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer, POS bombPos, vector<POS>& vecEffect)
{
	// PlaySoundID(SOUNDID::EXPLOSION, false);
	// 
	// gameMap[bombPos.y][bombPos.x] = (char)Tile::ROAD;
	// 
	// const int POWER = pPlayer->state.bombpower; // ��ź �Ŀ�
	// const int MAP_LIMIT_WIDTH = MAP_WIDTH - 2;
	// const int MAP_LIMIT_HEIGHT = MAP_HEIGHT - 1;
	// int bombMinX = std::clamp(bombPos.x - POWER, 0, MAP_LIMIT_WIDTH);
	// int bombMaxX = std::clamp(bombPos.x + POWER, 0, MAP_LIMIT_WIDTH);
	// int bombMinY = std::clamp(bombPos.y - POWER, 0, MAP_LIMIT_HEIGHT);
	// int bombMaxY = std::clamp(bombPos.y + POWER, 0, MAP_LIMIT_HEIGHT);
	// 
	// for (int i = bombMinY; i <= bombMaxY; ++i)
	// {
	// 	vecEffect.push_back({ bombPos.x, i });
	// 	if (gameMap[i][bombPos.x] == (char)Tile::WALL)
	// 		gameMap[i][bombPos.x] = (char)Tile::ROAD; // RODO : ITEMDROP
	// 
	// }
	// for (int i = bombMinX; i <= bombMaxX; ++i)
	// {
	// 	POS newPos = { i, bombPos.y };
	// 	if(std::find(vecEffect.begin(), vecEffect.end(), newPos) == vecEffect.end())
	// 	{
	// 		vecEffect.push_back({ i, bombPos.y });
	// 		if (gameMap[bombPos.y][i] == (char)Tile::WALL)
	// 			gameMap[bombPos.y][i] = (char)Tile::ROAD; // RODO : ITEMDROP
	// 
	// 	}
	// }
	// 
	// // ������ ���ʷ�'
	// 
	// const POS& playerPos = pPlayer->pos.tPos;
	// int dx = std::abs(playerPos.x - bombPos.x);
	// int dy = std::abs(playerPos.y - bombPos.y);
	// 
	// if ((dx == 0 || dx <= POWER) && (dy == 0 || dy <= POWER))
	// {
	// 	pPlayer->pos.tPos = pPlayer->pos.tStartPos;
	// }
	// 
	// // if (std::find(vecEffect.begin(), vecEffect.end(), pPlayer->position.tPos) == vecEffect.end())
	// //		pPlayer->position.tPos = pPlayer->position.tStartPos;
}

void RemoveDeadBomb()
{
	// vector<BOMB>::iterator iter = vecBomb.begin();
	// for (; iter != vecBomb.end();)
	// {
	// 	if (iter->isDie && iter->vecEffect.empty())
	// 		iter = vecBomb.erase(iter);
	// 	else
	// 		iter++;
	// 	// erase : ����� -> �ε����� ����� -> ũ�⵵ ����.
	// }
}

void Render(char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer, vector<Enemy>* pEnemy)
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			// �÷��̾� �׸���
			if (pPlayer->pos.tPos.x == j && pPlayer->pos.tPos.y == i)
				cout << "��";
			// Ÿ�� �׸���
			else
			{
				if (gameMap[i][j] == (char)Tile::WALL)
					cout << "��";
				else if (gameMap[i][j] == (char)Tile::ROAD)
					cout << "  ";
				// else if (gameMap[i][j] == (char)Tile::START)
				// 	cout << "��";
				// else if (gameMap[i][j] == (char)Tile::GOAL)
				// 	cout << "��";
				// else if (gameMap[i][j] == (char)Tile::BOMB)
				// 	cout << "��";
				// else if (gameMap[i][j] == (char)Tile::FLASH_BOMB)
				// 	cout << "��";
				// else if (gameMap[i][j] == (char)Tile::EXTRA_BOMB)
				// 	cout << "��";
				// else if (gameMap[i][j] == (char)Tile::SLIME)
				// 	cout << "��";
				// else if (gameMap[i][j] == (char)Tile::PUSH)
				// 	cout << "��";
			}
		}
		cout << endl;
	}
	RenderEffect();
	RenderUI(pPlayer);
}

void RenderUI(Player* pPlayer)
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 2;
	int y = resolution.Y / 10;
	Gotoxy(x, y++);
	cout << "=================" << endl;
	Gotoxy(x, y++);
	cout << "[ �÷��̾� ���� ]" << endl;
	Gotoxy(x, y++);
	cout << "-----------------" << endl;
	Gotoxy(x, y++);
	// cout << "��ź �Ŀ� : " << pPlayer->state.bombpower << endl;
	// Gotoxy(x, y++);
	// cout << "��ź ���� : " << pPlayer->state.bombcnt << endl;
	// Gotoxy(x, y++);
	// cout << "Push �ɷ� : " << (pPlayer->state.isPushOnOff ? "ON " : "OFF") << endl;
	// Gotoxy(x, y++);
	// cout << "������ �ɷ� : " << (pPlayer->state.isTrans ? "ON " : "OFF") << endl;
	// Gotoxy(x, y++);
	cout << "=================" << endl;
}

void GameScene(Scene& eCurScene, char gameMap[MAP_HEIGHT][MAP_WIDTH], Player* pPlayer, vector<Enemy>* pEnemies)
{
	Update(gameMap, pPlayer, eCurScene);
	//system("cls");
	Gotoxy(0, 0);
	Render(gameMap, pPlayer, pEnemies);

	FrameSync(60);
}

void InfoScene(Scene& eCurScene)
{
	// Update - ESCŰ�� ������ TITLE������ ���ư��� �غ���.
	Key key = KeyController();
	if (key == Key::ESC)
	{
		eCurScene = Scene::TITLE;
		system("cls");
	}
	RenderInfo();
}

void RenderInfo()
{
	cout << "���۹�" << endl;
}

void RenderEffect()
{
	SetColor(COLOR::RED);
	// for (auto& bomb : vecBomb)
	// {
	// 	if (!bomb.isDie)
	// 		continue;
	// 	for (auto& effect : bomb.vecEffect)
	// 	{
	// 		Gotoxy(effect.x * 2, effect.y);
	// 		cout << "��";
	// 		Sleep(10);
	// 	}
	// 	bomb.vecEffect.clear();
	// }
	SetColor();
}
