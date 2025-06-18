#include "GameLogic.h"
#include "Core.h"
#include "Console.h"
#include "Mci.h"
#include "TitleScene.h"
#include "KeyController.h"
#include <algorithm>
#include <fstream>

void GameLogic::Initialized()
{
	SetConsoleFont(L"NSimSun", { 20, 20 }, FW_BOLD);

	// ���� �ʱ�ȭ
	if (!InitAllSounds()) return;

	PlaySoundID(SOUNDID::BGM, true);

	// �ܼ�â ���� �ʱ�ȭ
	SetConsoleSettings(800, 600, false, L"HackMan");
	SetCursorVisual(true, 50);
	LoadStage();
	PlayerInit();
}

void GameLogic::PlayerInit()
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (gameMap[i][j] == (char)Tile::PLAYER_START)
				player._pos.tStartPos = { j, i };
		}
	}
	player._pos.tPos = player._pos.tStartPos;
	player._state = { true, false, false, false, false };
}

void GameLogic::EnemyInit()
{
	for (auto pEnemy : enemies)
	{
		// �� �����Ϳ� ���ؼ� �÷��̾� ��ġ ����
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			for (int j = 0; j < MAP_WIDTH; ++j)
			{
				if (gameMap[i][j] == (char)Tile::ENEMY_START)
					pEnemy._pos.tStartPos = { j, i };
			}
		}
		pEnemy._pos.tPos = pEnemy._pos.tStartPos;
		pEnemy._state = { false };
	}
}

void GameLogic::LoadStage()
{
	std::ifstream mapFile("Stage.txt");
	if (mapFile.is_open())
	{
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			// mapFile.getline(gameMap[i], MAP_WIDTH);
			mapFile >> *gameMap[i];
		}
		mapFile.close();
		return;
	}
	else
		cout << "�� ���� �ʱ�ȭ ����" << endl;
}

void GameLogic::Update()
{
	HandleInput();
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		return;

	// if (pPlayer->pos.tPos == pPlayer->pos.tEndPos)
	// {
	// 	// PlaySound();
	// 	eCurScene = Scene::QUIT;
	// }
}

void GameLogic::HandleInput()
{
	player._pos.tNewPos = player._pos.tPos;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::UP:
		--player._pos.tNewPos.y;
		break;
	case Key::DOWN:
		++player._pos.tNewPos.y;
		break;
	case Key::LEFT:
		--player._pos.tNewPos.x;
		break;
	case Key::RIGHT:
		++player._pos.tNewPos.x;
		break;
	case Key::SPACE: // ��ų
		//SpawnBomb(gameMap, pPlayer, vecBomb);
		break;
	}
	// clamp�Լ��� c++17�� ����
	player._pos.tNewPos.x = std::clamp(player._pos.tNewPos.x, 0, MAP_WIDTH - 2);
	player._pos.tNewPos.y = std::clamp(player._pos.tNewPos.y, 0, MAP_HEIGHT - 1);

	if (gameMap[player._pos.tNewPos.y][player._pos.tNewPos.x] != (char)Tile::WALL)
		player._pos.tPos = player._pos.tNewPos;
}

void GameLogic::Render()
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			// �÷��̾� �׸���
			if (player._pos.tPos.x == j && player._pos.tPos.y == i)
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
	RenderUI();
}

void GameLogic::RenderUI()
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

void GameLogic::GameScene()
{
	Update();
	//system("cls");
	Gotoxy(0, 0);
	Render();

	FrameSync(30);
}

void GameLogic::InfoScene()
{
	// Update - ESCŰ�� ������ TITLE������ ���ư��� �غ���.
	Key key = KeyController();
	if (key == Key::ESC)
	{
		*pCurScene = Scene::TITLE;
		system("cls");
	}
	RenderInfo();
}

void GameLogic::RenderInfo()
{
	cout << "���۹�" << endl;
}

void GameLogic::RenderEffect()
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
