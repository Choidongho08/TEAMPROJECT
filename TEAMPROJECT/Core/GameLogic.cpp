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

	// ���� �ʱ�ȭ
	// if (!InitAllSounds()) return;

	PlaySoundID(SOUNDID::BGM, true);

	// �ܼ�â ���� �ʱ�ȭ
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
		// �ʱ�ȭ
		std::string line;

		int row = 0;
		int col = 0;

		while (std::getline(mapFile, line))
		{
			if (row == 0)
				col = line.length(); // ù ���� ���� ���� �� �� ����

			row++;

			std::vector<int> mapRow;

			for (char ch : line)
			{
				mapRow.push_back(ch - '0');
			}

			_gameMap.InitializeMap(mapRow);
		} // �� ���� ���ϸ鼭 �� �ʱ�ȭ

		_gameMap.SetMapRowCol(row, col);
		mapFile.close();
		return;
	}
	else
		cout << "�� ���� �ʱ�ȭ ����" << endl;
}

void GameLogic::EntityInit()
{
	_player = Player();
	_player.Initialize(_gameMap.GetMapRow(), _gameMap.GetMapRow(), &_gameMap);


	int enemyCnt = 0;
	for (int i = 0; i < _gameMap.GetMapRow(); ++i)
	{
		for (int j = 0; j < _gameMap.GetMapCol(); ++j)
		{
			if ((_gameMap).isTile(i, j, Tile::ENEMY_SPAWN))
			{
				Enemy enemy = Enemy(_gameMap);
				enemy._pos.tStartPos = { j, i };
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

		if (_gameMap.isTile(y, x, Tile::ROAD))
		{
			_gameMap.SetMapTile(y, x, Tile::ITEM);
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
	case Key::SPACE: // ��ų
		//SpawnBomb(gameMap, pPlayer, vecBomb);
		break;
	}
	// clamp�Լ��� c++17�� ����
	_player._pos.tNewPos.x = std::clamp(_player._pos.tNewPos.x, 0, _gameMap.GetMapCol());
	_player._pos.tNewPos.y = std::clamp(_player._pos.tNewPos.y, 0, _gameMap.GetMapRow());

	if(!_gameMap.isTile(_player._pos.tNewPos.y, _player._pos.tNewPos.x, Tile::WALL))
		_player._pos.tPos = _player._pos.tNewPos;
}

void GameLogic::Render()
{
	for (int i = 0; i < _gameMap.GetMapRow(); ++i)
	{
		for (int j = 0; j < _gameMap.GetMapCol(); ++j)
		{
			// �÷��̾� �׸���
			if (_player._pos.tPos.x == j && _player._pos.tPos.y == i)
				cout << "��";
			// Ÿ�� �׸���
			else
			{
				if (_gameMap.isTile(i,j, Tile::WALL))
					cout << "��";
				else if (_gameMap.isTile(i, j, Tile::ROAD))
					cout << "  ";
				else if (_gameMap.isTile(i, j, Tile::PLAYER_START))
					cout << "  ";
				else if (_gameMap.isTile(i, j, Tile::ITEM))
					cout << "��";
				else if (_gameMap.isTile(i, j, Tile::ENEMY))
					cout << "  ";
				else if (_gameMap.isTile(i, j, Tile::ENEMY_SPAWN))
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
		skill = "�� �� ����";
		break;
	}
	 COORD resolution = GetConsoleResolution();
	 int x = resolution.X / 1.5;
	 int y = resolution.Y / 10;
	 Gotoxy(x, y++);
	 cout << "=======================" << endl;
	 Gotoxy(x, y++);
	 cout << "���� ���� ��ų : " << skill << endl;
	 if (_player._state.isHaveSkill) {
		 Gotoxy(x, y++);
		 cout << "-----------------------" << endl;
		 Gotoxy(x, y++);
		 cout << "-                     -" << endl;
		 Gotoxy(x, y++);
		 cout << "-    ���̶� �츶��    -" << endl;
		 Gotoxy(x, y++);
		 cout << "-                     -" << endl;
		 Gotoxy(x, y++);
		 cout << "-----------------------" << endl;
	 }
	 else
	 {
		 Gotoxy(x, y++);
		 cout << "-----------------------" << endl;
		 Gotoxy(x, y++);
		 cout << "-                     -" << endl;
		 Gotoxy(x, y++);
		 cout << "-                     -" << endl;
		 Gotoxy(x, y++);
		 cout << "-                     -" << endl;
		 Gotoxy(x, y++);
		 cout << "-----------------------" << endl;
	 }

	 Gotoxy(x, y++);
	 cout << "-----------------------" << endl;
	 Gotoxy(x, y++);
	 cout << "-                     -" << endl;
	 Gotoxy(x, y++);
	 cout << "-    ���ھ� : 0       -" << endl;
	 Gotoxy(x, y++);
	 cout << "-                     -" << endl;
	 Gotoxy(x, y++);
	 cout << "-----------------------" << endl;
	
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
	// Update - ESCŰ�� ������ TITLE������ ���ư��� �غ���.
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
	 cout << "[    ����      ���   ]" << endl;
	 Gotoxy(x, y++);
	 cout << "-----------------------" << endl;
	 Gotoxy(x, y++);
	 cout << "����Ű : ��, ��, ��, ��"  << endl;
	 Gotoxy(x, y++);
	 cout << "��ų : �����̽���      " << endl;
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
	// 		cout << "��";
	// 		Sleep(10);
	// 	}
	// 	bomb.vecEffect.clear();
	// }
	SetColor();
}
