#include "GameLogic.h"
#include "Core.h"
#include "Console.h"
#include "Mci.h"
#include "TitleScene.h"
#include "KeyController.h"
#include <algorithm>
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

	// 사운드 초기화

	PlaySoundID(SOUNDID::GAME, true);

	// 콘솔창 관련 초기화
	
	map.LoadStage();
	map.ItemInit();
	SetCursorVisual(true, 50);
	EntityInit();

	PlayerManager.player.OnKillEnemy = std::bind(&EnemyManager::DeadEnemy2, &EnemyManager, std::placeholders::_1);
}

void GameScene::EntityInit()
{
	PlayerManager.SpawnPlayer(entities);
	EnemyManager.SpawnEnemies(&entities, &PlayerManager.player);
}

void GameScene::Update()
{
	//system("cls");
	GotoXY(0, 0);
	HandleInput();
	EntitiesMove();
	EntityUpdate();
	Render();
	
	FrameSync(7);

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
			enemy.SettingAStar();
			enemy.Move();
			// enemy.pos.tPos.x = std::clamp(enemy.pos.tPos.x, 0, map.COL);
			// enemy.pos.tPos.y = std::clamp(enemy.pos.tPos.y, 0, map.ROW);
			enemy.pos.tForward = enemy.pos.tNewPos - enemy.pos.tPos;

			if (enemy.pos.tPos == PlayerManager.player.pos.tPos)
			{
				PlayerManager.PlayerDead();
				Core::Instance->ChangeScene(SCENE::DEAD);
			}
		}
	}
}

void GameScene::EntityUpdate()
{
	PlayerManager.player.Update();

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
		PlayerManager.player.UseSkill();
		break;
	}
	PlayerManager.player.pos.tNewPos.x = std::clamp(PlayerManager.player.pos.tNewPos.x, 0, map.COL);
	PlayerManager.player.pos.tNewPos.y = std::clamp(PlayerManager.player.pos.tNewPos.y, 0, map.ROW);
}

void GameScene::Render()
{
	COORD resolution = GetConsoleResolution();
	int offsetX = (resolution.X - map.COL * 2) / 2;
	int offsetY = 2;
	// 맵 렌더
	map.Render(PlayerManager.player.pos.tPos.x, PlayerManager.player.pos.tPos.y, PlayerManager.player.state.curSight);
	
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
							GotoXY(offsetX + j * 2, offsetY + i);
							cout << "EM";
							//entity->Render("EM");
						}
					}
					// 플레이어 그리기
					else if (entity->type == ENTITY_TYPE::Player)
					{
						if (entity->pos.tPos.x == j && entity->pos.tPos.y == i)
						{
							GotoXY(offsetX + j * 2, offsetY + i);
							cout << "⊙";
							//entity->Render("⊙");
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
	switch (PlayerManager.player.state.haveSkill)
	{
	case SKILL::None:
		skill = "NONE ";
		break;
	case SKILL::KILL:
		skill = "KILL ";
		break;
	case SKILL::SIGHT:
		skill = "SIGHT";
		break;
	case SKILL::DASH:
		skill = "DASH ";
		break;
	default:
		skill = "알 수 없음";
		break;
	}
	COORD resolution = GetConsoleResolution();
	int x = (resolution.X - 23) / 2 - 20;
	int y = map.ROW + 5;
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
		 if(PlayerManager.player.state.haveSkill == SKILL::DASH)
			cout << "-       ▶▶▶        -" << endl;
		 else if(PlayerManager.player.state.haveSkill == SKILL::KILL)
			wcout << "-       -- X --       -" << endl;
		 else if(PlayerManager.player.state.haveSkill == SKILL::SIGHT)
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
	 x = (resolution.X - 23) / 2 + 20;
	 y = map.ROW + 5;
	 GotoXY(x, y++);
	 cout << "=======================" << endl;
	 GotoXY(x, y++);
	 cout << "    현재     스코어    "<< endl;
	 GotoXY(x, y++);
	 cout << "-----------------------" << endl;
	 GotoXY(x, y++);
	 cout << "-                     -" << endl;
	 GotoXY(x, y++);
	 cout << "   스코어 :  " << PlayerManager.player.state.score << endl;
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
