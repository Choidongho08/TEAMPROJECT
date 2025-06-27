#include "GameLogic.h"
#include "Core.h"
#include "Console.h"
#include "Mci.h"
#include "TitleScene.h"
#include "KeyController.h"
#include <algorithm>
#include <fstream>
#include <random>
#include <format>
#include <future>
#include <thread>

using std::format;

GameScene::GameScene() : EnemyManager(&map), PlayerManager(&map)
{
}

void GameScene::SceneInit(SCENE _type, vector<AsciiObject>* _asciiObjects)
{
	asciiObjects = _asciiObjects;

	SetConsoleFont(L"NSimSun", { 20, 20 }, FW_BOLD);

	// 사운드 초기화

	PlaySoundID(SOUNDID::GAME, true);

	// 콘솔창 관련 초기화
	SetConsoleSettings(1200, 600, false, L"HackMan");
	SetCursorVisual(true, 50);

	LoadStage();
	ItemInit();
	EntityInit();
}

void GameScene::LoadStage()
{
	srand((unsigned int)time(NULL));
	int stageNumber = rand() % 3 + 1;
	string mapFileName = "Stage" + std::to_string(stageNumber) + ".txt";
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
			x = 0;
			std::vector<Node> rowGrid;
			for (char ch : line)
			{
				Node node = Node(ch - '0', x, y);	
				rowGrid.push_back(node);
				x++;
			}
			grid.push_back(rowGrid);
			y++;
		} // 맵 길이 구하면서 맵 초기화

		map.InitializeMap(grid);
		map.SetMapRowCol(y, x);
		mapFile.close();
		return;
	}
	else
		cout << "맵 파일 초기화 실패" << endl;
}

void GameScene::EntityInit()
{
	PlayerManager.SpawnPlayer(entities);
	EnemyManager.SpawnEnemies(&entities, &PlayerManager.player);
}

void GameScene::ItemInit()
{
	int itemCount = 0;
	srand((unsigned int)time(NULL));
	while (itemCount < map.MaxItemCnt)
	{
		int y = rand() % map.ROW;
		int x = rand() % map.COL;

		if (map.isTile(x, y, Tile::COIN))
		{
			map.SetMapTile(x, y, Tile::ITEM);
			itemCount++;
		}
	}
}

void GameScene::Update()
{
	//system("cls");
	GotoXY(0, 0);
	HandleInput();
	EntitiesMove();
	EntityUpdate();
	Render();
	
	FrameSync(6);

	// if (pPlayer->pos.tPos == pPlayer->pos.tEndPos)
	// {
	// 	// PlaySound();
	// 	eCurScene = Scene::QUIT;
	// }
}

void GameScene::EntitiesMove()
{
	for (auto enemy : EnemyManager.Enemies)
	{
		if (enemy.state.isAlive)
		{
			enemy.Move(&map);
			enemy.pos.tPos.x = std::clamp(enemy.pos.tPos.x, 0, map.COL);
			enemy.pos.tPos.y = std::clamp(enemy.pos.tPos.y, 0, map.ROW);
			enemy.pos.tForward = enemy.pos.tNewPos - enemy.pos.tPos;
		}
		if (enemy.pos.tPos == PlayerManager.player.pos.tPos)
		{
			PlayerManager.PlayerDead();
			Core::Instance->ChangeScene(SCENE::DEAD);
		}
	}
}

void GameScene::EntityUpdate()
{
	PlayerManager.player.Update(map);

	for (auto enemy : EnemyManager.Enemies)
	{
		enemy.Update();
	}
}

void GameScene::HandleInput()
{
	PlayerManager.player.pos.tNewPos = PlayerManager.player.pos.tPos;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::UP:
		--PlayerManager.player.pos.tNewPos.y;
		PlayerManager.player.pos.tForward = { 0, -1 };
		break;
	case Key::DOWN:
		++PlayerManager.player.pos.tNewPos.y;
		PlayerManager.player.pos.tForward = { 0, 1 };
		break;
	case Key::LEFT:
		--PlayerManager.player.pos.tNewPos.x;
		PlayerManager.player.pos.tForward = { -1, 0 };
		break;
	case Key::RIGHT:
		++PlayerManager.player.pos.tNewPos.x;
		PlayerManager.player.pos.tForward = { 1, 0 };
		break;
	case Key::SPACE:
		if(PlayerManager.player.UseSkill())
		{
			while (PlayerManager.player.state.isUsingSkill)
			{
				if (PlayerManager.player.state.usingSkill == Skill::DASH)
				{
					POS dashEndPos{ 0,0 };
					int num = 1;
					while (true)
					{
						dashEndPos = (PlayerManager.player.pos.tForward * num) + PlayerManager.player.pos.tPos;
						if (map.isTile(dashEndPos.x, dashEndPos.y, Tile::WALL))
						{
							dashEndPos = dashEndPos - PlayerManager.player.pos.tForward;
							PlayerManager.player.state.isUsingSkill = false;
							break;
						}
						num++;
						PlayerManager.player.pos.tNewPos = dashEndPos;
					}
				}
				else if (PlayerManager.player.state.usingSkill == Skill::KILL)
				{
					POS targetPos = PlayerManager.player.pos.tForward + PlayerManager.player.pos.tPos;
					for (const Enemy& enemy : EnemyManager.Enemies)
					{
						if (enemy.pos.tPos == targetPos)
						{
							EnemyManager.DeadEnemy(enemy);
							break;
						}
					}
					PlayerManager.player.state.isUsingSkill = false;
				}
				else if (PlayerManager.player.state.usingSkill == Skill::SIGHT)
				{
					const int& sight = PlayerManager.player.state.maxSight;
					PlayerManager.player.SetSightTime(3);
					PlayerManager.player.SetSight(sight * 2);
					break;
				}
			}
		}
		break;
	}
	PlayerManager.player.Move(&map);
	PlayerManager.player.CheckTile(&map);
	PlayerManager.player.pos.tPos.x = std::clamp(PlayerManager.player.pos.tPos.x, 0, map.COL);
	PlayerManager.player.pos.tPos.y = std::clamp(PlayerManager.player.pos.tPos.y, 0, map.ROW);
}

void GameScene::Render()
{
	// 맵 렌더
	map.Render(PlayerManager.player.pos.tPos.x, PlayerManager.player.pos.tPos.y, PlayerManager.player.state.maxSight);
	
	for (int i = 0; i < map.ROW; ++i)
	{
		for (int j = 0; j < map.COL; ++j)
		{
			
			for (auto entity : entities)
			{
				if (entity->state.isAlive)
				{
					// 적 그리기
					if (entity->type == ENTITY_TYPE::Enemy)
					{
						if (entity->pos.tPos.x == j && entity->pos.tPos.y == i)
						{
							entity->Render("EM");
						}
					}
					// 플레이어 그리기
					else if (entity->type == ENTITY_TYPE::Player)
					{
						if (entity->pos.tPos.x == j && entity->pos.tPos.y == i)
						{
							entity->Render("⊙");
						}
					}
				}
				else
					entity->Render("  ");
			}
		}
		cout << endl;
	}
	RenderEffect();
	RenderUI();
}

void GameScene::RenderUI()
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
	int x = map.COL - (23 / 2);
	 int y = map.ROW + 2;
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
			cout << "-       ▶▶▶        -" << endl;
		 else if(PlayerManager.player.state.whatSkill == Skill::KILL)
			wcout << "-       -- X --       -" << endl;
		 else if(PlayerManager.player.state.whatSkill == Skill::SIGHT)
			cout << "-      << ○ >>       -" << endl;
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
	 cout << "     스코어 :  " << PlayerManager.player.state.score << " / " << map.MapCoinCnt << endl;
	 GotoXY(x, y++);
	 cout << "-                     -" << endl;
	 GotoXY(x, y++);
	 cout << "-----------------------" << endl;
}

void GameScene::RenderEffect()
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
