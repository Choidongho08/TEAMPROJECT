#include "GameLogic.h"
#include "Core.h"
#include "Console.h"
#include "Mci.h"
#include "TitleScene.h"
#include "KeyController.h"
#include <algorithm>
#include <fstream>
#include<random>
#include <format>
using std::format;

GameLogic::GameLogic()
{
	_pObjs = nullptr;
	_pGameMap = nullptr;

	MAP_HEIGHT = 0;
	MAP_WIDTH = 0;
	maxFollowingEnemyCnt = 2;
}

void GameLogic::Initialized(
	vector<AsciiObject>* objs,
	std::vector<std::vector<char>>* gameMap,
	int maxFollowingEnemy
)
{
	_pObjs = objs;
	_pGameMap = gameMap;

	SetConsoleFont(L"NSimSun", { 20, 20 }, FW_BOLD);

	// 사운드 초기화
	// if (!InitAllSounds()) return;

	PlaySoundID(SOUNDID::BGM, true);

	// 콘솔창 관련 초기화
	SetConsoleSettings(800, 600, false, L"HackMan");
	SetCursorVisual(true, 50);
	
	LoadStage();
	ItemInit();

	PlayerInit();
	EnemyInit();
}

void GameLogic::PlayerInit()
{
	_player = Player();

	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if ((*_pGameMap)[i][j] == (char)Tile::PLAYER_START)
				_player._pos.tStartPos = { j, i };
		}
	}
	_player._pos.tPos = _player._pos.tStartPos;
	_player._state = { true, false, false, false, false };
	_player.Initialize(MAP_HEIGHT, MAP_WIDTH, _pGameMap);
}

void GameLogic::EnemyInit()
{
	int enemyCnt = 0;
	for (auto enemy : _enemies)
	{
		enemy = Enemy();
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			for (int j = 0; j < MAP_WIDTH; ++j)
			{
				if ((*_pGameMap)[i][j] == (char)Tile::ENEMY_SPAWN)
					enemy._pos.tStartPos = { j, i };
				enemy.Initialize(POS{ j, i }, enemyCnt < maxFollowingEnemyCnt);
			}
		}
		enemy._pos.tPos = enemy._pos.tStartPos;
		enemy._state = { false };
	}
	enemyCnt++;
}


void GameLogic::LoadStage()
{
	srand((unsigned int)time(NULL));
	int stageNumber = rand() % 3 + 1;
	string mapFileName = "Stage" + std::to_string(stageNumber) + ".txt";
	std::ifstream mapFile(mapFileName);
	if (mapFile.is_open())
	{
		// 초기화
		std::string line;
		_pGameMap->clear();

		while (std::getline(mapFile, line))
		{
			if (MAP_HEIGHT == 0)
				MAP_WIDTH = line.length(); // 첫 줄의 문자 수로 열 수 결정

			MAP_HEIGHT++;

			std::vector<char> mapHeight;

			for (char ch : line)
			{
				mapHeight.push_back(ch);
			}
			// mapHeight.push_back(' '); // 마지막  null
			_pGameMap->push_back(mapHeight);
		} // 맵 길이 구하면서 맵 초기화

		mapFile.close();
		return;
	}
	else
		cout << "맵 파일 초기화 실패" << endl;
}

void GameLogic::ItemInit()
{
	int itemCount = 0;
	srand((unsigned int)time(NULL));
	while (itemCount < 5)
	{
		int y = rand() % MAP_HEIGHT;
		int x = rand() % MAP_WIDTH;

		if ((*_pGameMap)[y][x] == (char)Tile::ROAD)
		{
			(*_pGameMap)[y][x] = (char)Tile::ITEM;
			itemCount++;
		}
	}
}


void GameLogic::Update()
{
	GameScene();
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
	_player._pos.tNewPos = _player._pos.tPos;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::UP:
		--_player._pos.tNewPos.y;
		break;
	case Key::DOWN:
		++_player._pos.tNewPos.y;
		break;
	case Key::LEFT:
		--_player._pos.tNewPos.x;
		break;
	case Key::RIGHT:
		++_player._pos.tNewPos.x;
		break;
	case Key::SPACE: // 스킬
		//SpawnBomb(gameMap, pPlayer, vecBomb);
		break;
	}
	// clamp함수는 c++17에 나옴
	_player._pos.tNewPos.x = std::clamp(_player._pos.tNewPos.x, 0, MAP_WIDTH);
	_player._pos.tNewPos.y = std::clamp(_player._pos.tNewPos.y, 0, MAP_HEIGHT);

	if ((*_pGameMap)[_player._pos.tNewPos.y][_player._pos.tNewPos.x] != (char)Tile::WALL)
		_player._pos.tPos = _player._pos.tNewPos;
}

void GameLogic::Render()
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			// 플레이어 그리기
			if (_player._pos.tPos.x == j && _player._pos.tPos.y == i)
				cout << "⊙";
			// 타일 그리기
			else
			{
				if ((*_pGameMap)[i][j] == (char)Tile::WALL)
					cout << "■";
				else if ((*_pGameMap)[i][j] == (char)Tile::ROAD)
					cout << "  ";
				else if ((*_pGameMap)[i][j] == (char)Tile::PLAYER_START)
					cout << "  ";
				else if ((*_pGameMap)[i][j] == (char)Tile::ITEM)
					cout << "★";
				else if ((*_pGameMap)[i][j] == (char)Tile::ENEMY)
					cout << "  ";
				else if ((*_pGameMap)[i][j] == (char)Tile::ENEMY_SPAWN)
					cout << "  ";
			}
		}
		cout << endl;
	}
	RenderEffect();
	RenderUI();
}

void GameLogic::RenderUI()
{
	// COORD resolution = GetConsoleResolution();
	// int x = resolution.X / 2;
	// int y = resolution.Y / 10;
	// Gotoxy(x, y++);
	// cout << "=================" << endl;
	// Gotoxy(x, y++);
	// cout << "[ 플레이어 상태 ]" << endl;
	// Gotoxy(x, y++);
	// cout << "-----------------" << endl;
	// Gotoxy(x, y++);
	// cout << "폭탄 파워 : " << pPlayer->state.bombpower << endl;
	// Gotoxy(x, y++);
	// cout << "폭탄 개수 : " << pPlayer->state.bombcnt << endl;
	// Gotoxy(x, y++);
	// cout << "Push 능력 : " << (pPlayer->state.isPushOnOff ? "ON " : "OFF") << endl;
	// Gotoxy(x, y++);
	// cout << "슬라임 능력 : " << (pPlayer->state.isTrans ? "ON " : "OFF") << endl;
	// Gotoxy(x, y++);
	// cout << "=================" << endl;
}

void GameLogic::GameScene()
{
	//system("cls");
	Gotoxy(0, 0);
	HandleInput();
	Render();

	FrameSync(8);
}

void GameLogic::InfoScene()
{
	// Update - ESC키를 눌러서 TITLE씬으로 돌아가게 해보자.
	Key key = KeyController();
	if (key == Key::ESC)
	{
		Core::Instance->ChangeScene(Scene::TITLE);
		system("cls");
	}
	Gotoxy(0, 0);
	RenderInfo();
}

void GameLogic::InfoSceneInit()
{
	system("cls");
}

void GameLogic::RenderInfo()
{
	 COORD resolution = GetConsoleResolution();
	 int x = resolution.X/ 3;
	 int y = resolution.Y/3;
	 Gotoxy(x, y++);
	 cout << "=======================" << endl;
	 Gotoxy(x, y++);
	 cout << "[    조작      방법   ]" << endl;
	 Gotoxy(x, y++);
	 cout << "-----------------------" << endl;
	 Gotoxy(x, y++);
	 cout << "조작키 : ↑, →, ←, ↓"  << endl;
	 Gotoxy(x, y++);
	 cout << "스킬 : 키가 뭐야 동호야 " << endl;
	 Gotoxy(x, y++);
	 cout << "=======================" << endl;
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
	// 		cout << "▒";
	// 		Sleep(10);
	// 	}
	// 	bomb.vecEffect.clear();
	// }
	SetColor();
}
