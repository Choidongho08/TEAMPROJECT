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

GameLogic::GameLogic() : EnemyManager(Map), PlayerManager(Map)
{
	pObjs = nullptr;
	maxFollowingEnemyCnt = 2;
}

void GameLogic::Initialized(
	vector<AsciiObject>* objs,
	int maxFollowingEnemy
)
{
	maxFollowingEnemyCnt = maxFollowingEnemy;
	pObjs = objs;

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
	string mapFileName = "Stage2.txt"; // + std::to_string(stageNumber) + ".txt";
	std::ifstream mapFile(mapFileName);
	if (mapFile.is_open())
	{
		// 초기화
		std::string line;

		int x = 0;
		int y = 0;

		std::vector<std::vector<Node>> grid;

		while (std::getline(mapFile, line))
		{
			std::vector<Node> rowGrid;
			for (char ch : line)
			{
				Node node = Node(ch - '0', x, y);
				rowGrid.push_back(node);
				GotoXY(0, 25);
				cout << x << ", " << y;
			}
			grid.push_back(rowGrid);

			x++;
			y++;
		} // 맵 길이 구하면서 맵 초기화

		Map.InitializeMap(grid);
		Map.SetMapRowCol(y, x);
		mapFile.close();
		return;
	}
	else
		cout << "맵 파일 초기화 실패" << endl;
}

void GameLogic::EntityInit()
{
	PlayerManager.SpawnPlayer(entities);
	EnemyManager.SpawnEnemies(entities);
}

void GameLogic::ItemInit()
{
	int itemCount = 0;
	srand((unsigned int)time(NULL));
	while (itemCount < Map.MaxItemCnt)
	{
		int y = rand() % Map.ROW;
		int x = rand() % Map.COL;

		if (Map.isTile(x, y, Tile::COIN))
		{
			Map.SetMapTile(x, y, Tile::ITEM);
			itemCount++;
		}
	}
}


void GameLogic::Update()
{
	//system("cls");
	GotoXY(0, 0);
	HandleInput();
	EntitiesMove();
	Render();

	FrameSync(6);

	// if (pPlayer->pos.tPos == pPlayer->pos.tEndPos)
	// {
	// 	// PlaySound();
	// 	eCurScene = Scene::QUIT;
	// }
}

void GameLogic::EntitiesMove()
{
	for (auto enemy : EnemyManager.Enemies)
	{
		enemy.Move();
		DebugLog("( " + std::to_string(enemy.pos.tPos.x) + ", " + std::to_string(enemy.pos.tPos.y) + " )");
	}
	for (auto entity : entities)
	{
		entity.Move(Map);
		entity.pos.tNewPos.x = std::clamp(entity.pos.tNewPos.x, 0, Map.COL);
		entity.pos.tNewPos.y = std::clamp(entity.pos.tNewPos.y, 0, Map.ROW);
		entity.pos.tForward = entity.pos.tNewPos - entity.pos.tPos;
	}
}

void GameLogic::HandleInput()
{
	PlayerManager.player.pos.tNewPos = PlayerManager.player.pos.tPos;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::UP:
		--PlayerManager.player.pos.tNewPos.y;
		break;
	case Key::DOWN:
		++PlayerManager.player.pos.tNewPos.y;
		break;
	case Key::LEFT:
		--PlayerManager.player.pos.tNewPos.x;
		break;
	case Key::RIGHT:
		++PlayerManager.player.pos.tNewPos.x;
		break;
	case Key::SPACE: // ��ų
		//SpawnBomb(gameMap, pPlayer, vecBomb);
		break;
	}
}

void GameLogic::Render()
{
	for (int i = 0; i < Map.ROW; ++i)
	{
		for (int j = 0; j < Map.COL; ++j)
		{
			for (auto entity : entities)
			{
				// 적 그리기
				if (entity.type == ENTITY_TYPE::Enemy)
				{
					if (entity.pos.tPos.x == j && entity.pos.tPos.y == i)
					{
						entity.Render("EM");
					}
				}
				// 플레이어 그리기
				else if (entity.type == ENTITY_TYPE::Player)
				{
					if (entity.pos.tPos.x == j && entity.pos.tPos.y == i)
					{
						entity.Render("⊙");
					}
				}
				
			}
			
			Map.Render(j, i);
		}
		cout << endl;
	}
	RenderEffect();
	RenderUI();
}

void GameLogic::RenderUI()
{
	string skill;
	switch (PlayerManager.player.skill)
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
	 // x = Map.COL + 10;
	 int y = resolution.Y / 10;
	 GotoXY(x, y++);
	 cout << "=======================" << endl;
	 GotoXY(x, y++);
	 cout << "현재 보유 스킬 : " << skill << endl;
	 if (PlayerManager.player.state.isHaveSkill) {
		 GotoXY(x, y++);
		 cout << "-----------------------" << endl;
		 GotoXY(x, y++);
		 cout << "-                     -" << endl;
		 GotoXY(x, y++);
		 if(PlayerManager.player.state.whatSkill == Skill::DASH)
			cout << "-       DASH       -" << endl;
		 else if(PlayerManager.player.state.whatSkill == Skill::KILL)
			cout << "-       KILL       -" << endl;
		 else if(PlayerManager.player.state.whatSkill == Skill::SIGHT)
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

	 logPos = POS{ x, y++ };
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
	 int y = resolution.Y / 3;
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

void GameLogic::DebugLog(std::string str)
{
	if (currDebugCnt >= maxDebugCnt)
		currDebugCnt = 0;

	GotoXY(logPos.x, logPos.y + currDebugCnt);
	cout << str;
	currDebugCnt++;
	GotoXY(0, 0);
}
