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
#include "../DH/Debug.h"
using std::format;

GameScene::GameScene() : EnemyManager(&Map), PlayerManager(&Map)
{
	pObjs = nullptr;
	maxFollowingEnemyCnt = 2;
}

void GameScene::Initialized(
	vector<AsciiObject>* objs,
	int maxFollowingEnemy
)
{
	Debug debug;
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

void GameScene::LoadStage()
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

		Map.InitializeMap(grid);
		Map.SetMapRowCol(y, x);
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

void GameScene::Update()
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

void GameScene::EntitiesMove()
{
	Player* player = &PlayerManager.player;
	player->Move(&Map);
	player->pos.tNewPos.x = std::clamp(player->pos.tNewPos.x, 0, Map.COL);
	player->pos.tNewPos.y = std::clamp(player->pos.tNewPos.y, 0, Map.ROW);
	PlayerManager.player.CheckTile(&Map);

	for (auto enemy : EnemyManager.Enemies)
	{
		if (enemy.state.isAlive)
		{
			enemy.Move(&Map);
			enemy.pos.tNewPos.x = std::clamp(enemy.pos.tNewPos.x, 0, Map.COL);
			enemy.pos.tNewPos.y = std::clamp(enemy.pos.tNewPos.y, 0, Map.ROW);
			enemy.pos.tForward = enemy.pos.tNewPos - enemy.pos.tPos;
		}
		if (enemy.pos.tPos == player->pos.tPos)
		{
			PlayerManager.PlayerDead();
			Core::Instance->ChangeScene(SCENE::DEAD);
		}
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

void GameScene::Render()
{
	for (int i = 0; i < Map.ROW; ++i)
	{
		for (int j = 0; j < Map.COL; ++j)
		{
			// 맵 렌더
			Map.Render(j, i);

			for (auto entity : entities)
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
	 cout << "     스코어 :  " << PlayerManager.player.state.score << endl;
	 GotoXY(x, y++);
	 cout << "-                     -" << endl;
	 GotoXY(x, y++);
	 cout << "-----------------------" << endl;
}

void GameScene::InfoScene()
{
	Key key = KeyController();

	bool isQNow = (key == Key::Q);
	bool isENow = (key == Key::E);

	if (key == Key::ESC)
	{
		Core::Instance->ChangeScene(SCENE::TITLE);
		system("cls");
	}
	else if (isQNow && !wasQPressed)
	{
		system("cls");
		RenderInfo(true);
	}
	else if (isENow && !wasEPressed)
	{
		system("cls");
		RenderInfo(false);
	}

	wasQPressed = isQNow;
	wasEPressed = isENow;

	GotoXY(0, 0);
}

void GameScene::InfoSceneInit()
{
	system("cls");
	RenderInfo(true);
}

void GameScene::DeadSceneInit()
{
}

void GameScene::RenderInfo(bool isTrue)
{
	 COORD resolution = GetConsoleResolution();
	 int x = resolution.X / 3;
	 int y = resolution.Y / 3;
	 if (isTrue) {
		 GotoXY(x, y++);
		 cout << "=======================  ▶";
		 GotoXY(x, y++);
		 cout << "[    조작      방법   ]";
		 GotoXY(x, y++);
		 cout << "-----------------------";
		 GotoXY(x, y++);
		 cout << " 조작키	: ↑ → ← ↓";
		 GotoXY(x, y++);
		 cout << " 스킬	: 스페이스바     ";
		 GotoXY(x, y++);
		 cout << " 다음 내용 보기 :  E   ";
		 GotoXY(x, y++);
		 cout << "=======================";
	 }
	 else {
		 GotoXY(x - 4, y++);
		 cout << "◀  ==========================";
		 GotoXY(x, y++);
		 cout << " [    게임      방법   ]";
		 GotoXY(x, y++);
		 cout << "--------------------------";
		 GotoXY(x, y++);
		 cout << "1. 적을 피해서 코인을 먹자";
		 GotoXY(x, y++);
		 cout << "2. 맵 곳곳에 아이템이 있다";
		 GotoXY(x, y++);
		 cout << "3. 아이템을 먹으면 스킬 획득";
		 GotoXY(x, y++);
		 cout << " - KILL  : 근처 적 제거";
		 GotoXY(x, y++);
		 cout << " - DASH  : 앞으로 대쉬";
		 GotoXY(x, y++);
		 cout << " - SIGHT : 시야 넓어짐 ";
		 GotoXY(x, y++);
		 cout << " 이전 내용 보기 : Q    ";
		 GotoXY(x, y++);
		 cout << "==========================";
	 }
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
