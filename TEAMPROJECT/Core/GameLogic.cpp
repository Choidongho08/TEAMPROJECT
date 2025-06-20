﻿#include "GameLogic.h"
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
	_maxFollowingEnemyCnt = 2;
	_gameMap = Map();
}

void GameLogic::Initialized(
	vector<AsciiObject>* objs,
	int maxFollowingEnemy
)
{
	_maxFollowingEnemyCnt = maxFollowingEnemy;
	_pObjs = objs;

	SetConsoleFont(L"NSimSun", { 20, 20 }, FW_BOLD);

	// 사운드 초기화
	// if (!InitAllSounds()) return;

	PlaySoundID(SOUNDID::BGM, true);

	// 콘솔창 관련 초기화
	SetConsoleSettings(1200, 600, false, L"HackMan");
	SetCursorVisual(true, 50);
	
	LoadStage();
	ItemInit();

	EntityInit();
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

		int row = 0;
		int col = 0;

		while (std::getline(mapFile, line))
		{
			if (row == 0)
				col = line.length(); // 첫 줄의 문자 수로 열 수 결정

			row++;

			std::vector<int> mapRow;

			for (char ch : line)
			{
				mapRow.push_back(ch - '0');
			}

			_gameMap.InitializeMap(mapRow);
		} // 맵 길이 구하면서 맵 초기화

		_gameMap.SetMapRowCol(row, col);
		mapFile.close();
		return;
	}
	else
		cout << "맵 파일 초기화 실패" << endl;
}

void GameLogic::EntityInit()
{
	_player = Player();
	_player.Initialize(_gameMap.GetMapCol(), _gameMap.GetMapRow(), &_gameMap);


	int enemyCnt = 0;
	for (int i = 0; i < _gameMap.GetMapRow(); ++i)
	{
		for (int j = 0; j < _gameMap.GetMapCol(); ++j)
		{
			if ((_gameMap).isTile(j, i, Tile::ENEMY_SPAWN))
			{
				Enemy enemy = Enemy(_gameMap);
				enemy.Initialize(POS{ j, i }, enemyCnt < _maxFollowingEnemyCnt);
				_enemies.push_back(enemy);
				enemyCnt++;
			}
		}
	}
}

void GameLogic::ItemInit()
{
	int itemCount = 0;
	srand((unsigned int)time(NULL));
	while (itemCount < 5)
	{
		int y = rand() % _gameMap.GetMapRow();
		int x = rand() % _gameMap.GetMapCol();

		if (_gameMap.isTile(x, y, Tile::COIN))
		{
			_gameMap.SetMapTile(x, y, Tile::ITEM);
			itemCount++;
		}
	}
}


void GameLogic::Update()
{
	//system("cls");
	GotoXY(0, 0);
	HandleInput();
	EnemiesMove();
	Render();

	FrameSync(6);

	// if (pPlayer->pos.tPos == pPlayer->pos.tEndPos)
	// {
	// 	// PlaySound();
	// 	eCurScene = Scene::QUIT;
	// }
}

void GameLogic::EnemiesMove()
{
	for (auto enemy : _enemies)
	{
		enemy.Move();
		DebugLog("" + enemy._pos.tPos.x + "" + enemy._pos.tPos.y);
	}
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
	case Key::SPACE: // ��ų
		//SpawnBomb(gameMap, pPlayer, vecBomb);
		break;
	}
	// clamp�Լ��� c++17�� ����
	_player._pos.tNewPos.x = std::clamp(_player._pos.tNewPos.x, 0, _gameMap.GetMapCol());
	_player._pos.tNewPos.y = std::clamp(_player._pos.tNewPos.y, 0, _gameMap.GetMapRow());

	_player._forward = _player._pos.tNewPos - _player._pos.tPos;

	if (!_gameMap.isTile(_player._pos.tNewPos.x, _player._pos.tNewPos.y, Tile::WALL))
		_player._pos.tPos = _player._pos.tNewPos;
	// _player.HandleInput(_gameMap);
}

void GameLogic::Render()
{
	for (int i = 0; i < _gameMap.GetMapRow(); ++i)
	{
		for (int j = 0; j < _gameMap.GetMapCol(); ++j)
		{
			for (auto enemy : _enemies)
			{
				if (enemy._pos.tPos.x == j && enemy._pos.tPos.y == i)
				{
					enemy.Render("zz");
				}
			}
			// 플레이어 그리기
			if (_player._pos.tPos.x == j && _player._pos.tPos.y == i)
				_player.Render("⊙");
				// _player.Render(j, i, "⊙");
			// 타일 그리기
			else
			{
				if (_gameMap.isTile(j,i, Tile::WALL))
					cout << "■";
				if (_gameMap.isTile(j,i, Tile::BROKEN_WALL))
					cout << "▩";
				else if (_gameMap.isTile(j, i, Tile::ROAD))
					cout << "  ";
				else if (_gameMap.isTile(j, i, Tile::COIN))
					cout << "·";
				else if (_gameMap.isTile(j, i, Tile::PLAYER_START))
					cout << "  ";
				else if (_gameMap.isTile(j, i, Tile::ITEM))
					cout << "★";
				// else if (_gameMap.isTile(j, i, Tile::ENEMY))
				// 	cout << "";
				// else if (_gameMap.isTile(j, i, Tile::ENEMY_SPAWN))
				// 	cout << "  ";
			}
		}
		cout << endl;
	}
	RenderEffect();
	RenderUI();
}

void GameLogic::RenderUI()
{
	string skill;
	switch (_player._skill)
	{
	case Skill::None:
		skill = "None";
		break;
	case Skill::KILL:
		skill = "KILL";
		break;
	case Skill::SIGHT:
		skill = "SIGHT";
		break;
	case Skill::DASH:
		skill = "DASH";
		break;
	default:
		skill = "알 수 없음";
		break;
	}
	 COORD resolution = GetConsoleResolution();
	 int x = resolution.X / 1.5;
	 int y = resolution.Y / 10;
	 GotoXY(x, y++);
	 cout << "=======================" << endl;
	 GotoXY(x, y++);
	 cout << "현재 보유 스킬 : " << skill << endl;
	 if (_player._state.isHaveSkill) {
		 GotoXY(x, y++);
		 cout << "-----------------------" << endl;
		 GotoXY(x, y++);
		 cout << "-                     -" << endl;
		 GotoXY(x, y++);
		 if(_player._state.whatSkill == Skill::DASH)
			cout << "-       DASH       -" << endl;
		 else if(_player._state.whatSkill == Skill::KILL)
			cout << "-       KILL       -" << endl;
		 else if(_player._state.whatSkill == Skill::SIGHT)
			cout << "-       SIGHT      -" << endl;
		 else
			cout << "-       NONE       -" << endl;
		 GotoXY(x, y++);
		 cout << "-                     -" << endl;
		 GotoXY(x, y++);
		 cout << "-----------------------" << endl;
	 }
	 else
	 {
		 GotoXY(x, y++);
		 cout << "-----------------------" << endl;
		 GotoXY(x, y++);
		 cout << "-                     -" << endl;
		 GotoXY(x, y++);
		 cout << "-                     -" << endl;
		 GotoXY(x, y++);
		 cout << "-                     -" << endl;
		 GotoXY(x, y++);
		 cout << "-----------------------" << endl;
	 }

	 GotoXY(x, y++);
	 cout << "-----------------------" << endl;
	 GotoXY(x, y++);
	 cout << "-                     -" << endl;
	 GotoXY(x, y++);
	 cout << "-    스코어 : 0       -" << endl;
	 GotoXY(x, y++);
	 cout << "-                     -" << endl;
	 GotoXY(x, y++);
	 cout << "-----------------------" << endl;
	
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
	GotoXY(0, 0);
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
	 GotoXY(x, y++);
	 cout << "=======================" << endl;
	 GotoXY(x, y++);
	 cout << "[    조작      방법   ]" << endl;
	 GotoXY(x, y++);
	 cout << "-----------------------" << endl;
	 GotoXY(x, y++);
	 cout << "조작키	: ↑ → ← ↓"  << endl;
	 GotoXY(x, y++);
	 cout << "스킬	: 스페이스바      " << endl;
	 GotoXY(x, y++);
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

void GameLogic::DebugLog(string str)
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 3;
	int y = resolution.Y / 3;
	GotoXY(x, y);
	cout << str;
}
