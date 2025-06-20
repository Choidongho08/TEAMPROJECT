﻿#include "TitleScene.h"
#include<io.h>
#include<fcntl.h>
#include "../Core/Console.h"
#include "AsciiObject.h"
#include "KeyController.h"
#include "Core.h"

TitleScene::TitleScene()
{
	_pObjs = nullptr;
	textColor = COLOR::WHITE;
	bgColor = COLOR::BLACK;
}

void TitleScene::Initialized(vector<AsciiObject>* objs)
{
	_pObjs = objs;
	textColor = COLOR::WHITE;
	bgColor = COLOR::BLACK;
}

void TitleScene::Render()
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 11;
	int y = resolution.Y / 7;
	int coutmode = _setmode(_fileno(stdout), _O_U16TEXT);

	GotoXY(x, ++y); wcout<<L" ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄    ▄       ▄▄       ▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄ " << endl;
	GotoXY(x, ++y); wcout<<L"▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌     ▐░░▌     ▐░░▌▐░░░░░░░░░░░▌▐░░▌      ▐░▌" << endl;
	GotoXY(x, ++y); wcout<<L"▐░▌       ▐░▌▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀ ▐░▌ ▐░▌      ▐░▌░▌   ▐░▐░▌▐░█▀▀▀▀▀▀▀█░▌▐░▌░▌     ▐░▌" << endl;
	GotoXY(x, ++y); wcout<<L"▐░▌       ▐░▌▐░▌       ▐░▌▐░▌          ▐░▌▐░▌       ▐░▌▐░▌ ▐░▌▐░▌▐░▌       ▐░▌▐░▌▐░▌    ▐░▌" << endl;
	GotoXY(x, ++y); wcout<<L"▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌▐░▌          ▐░▌░▌        ▐░▌ ▐░▐░▌ ▐░▌▐░█▄▄▄▄▄▄▄█░▌▐░▌ ▐░▌   ▐░▌" << endl;
	GotoXY(x, ++y); wcout<<L"▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌          ▐░░▌         ▐░▌  ▐░▌  ▐░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌  ▐░▌" << endl;
	GotoXY(x, ++y); wcout<<L"▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌▐░▌          ▐░▌░▌        ▐░▌   ▀   ▐░▌▐░█▀▀▀▀▀▀▀█░▌▐░▌   ▐░▌ ▐░▌" << endl;
	GotoXY(x, ++y); wcout<<L"▐░▌       ▐░▌▐░▌       ▐░▌▐░▌          ▐░▌▐░▌       ▐░▌       ▐░▌▐░▌       ▐░▌▐░▌    ▐░▌▐░▌" << endl;
	GotoXY(x, ++y); wcout<<L"▐░▌       ▐░▌▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄▄▄ ▐░▌ ▐░▌      ▐░▌       ▐░▌▐░▌       ▐░▌▐░▌     ▐░▐░▌" << endl;
	GotoXY(x, ++y); wcout<<L"▐░▌       ▐░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌  ▐░▌     ▐░▌       ▐░▌▐░▌       ▐░▌▐░▌      ▐░░▌" << endl;
	GotoXY(x, ++y); wcout<<L" ▀         ▀  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀    ▀       ▀         ▀  ▀         ▀  ▀        ▀▀ " << endl;




	int wcoutmode = _setmode(_fileno(stdout), coutmode);
	x = resolution.X / 2.5;
	y = resolution.Y / 3 * 2;
	GotoXY(x, y);
	cout << "게임 시작";
	GotoXY(x, y + 2);
	cout << "게임 정보";
	GotoXY(x, y + 4);
	cout << "게임 종료";

}

void TitleScene::Update()
{
	this->bgColor = COLOR::BLUE;
	// for (auto obj : *this->_pObjs)
	// {
	// 	obj.ObjectUpdate();
	// 	obj.ObjectRender(textColor, bgColor);
	// }
	
	if (Core::Instance->GetCurrentScene() != Scene::TITLE)
		return;

	Render();
	Sleep(30);

	Menu eMenu = GetCurMenu();
	switch (eMenu)
	{
	case Menu::START:
		EnterAnimation();
		Core::Instance->ChangeScene(Scene::GAME);
		break;
	case Menu::INFO:
		Core::Instance->ChangeScene(Scene::INFO);
		break;
	case Menu::QUIT:
		Core::Instance->ChangeScene(Scene::QUIT);
		break;
	}
	// for (auto obj : *(_pObjs))
	// {
	// 	obj.ObjectUpdate();
	// }
}

Menu TitleScene::GetCurMenu()
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 2.5;
	static int y = resolution.Y / 3 * 2;
	static int originY = y;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::UP:
		if (y > originY)
		{
			GotoXY(x - 5, y);
			cout << "    ";
			GotoXY(x + 10, y);
			cout << "  ";
			GotoXY(x - 4, ----y);
			cout << "  [";
			GotoXY(x + 10, y);
			cout << "]";
			Sleep(100);
		}
		break;
	case Key::DOWN:
		if (y < originY + 4)
		{
			GotoXY(x - 5, y);
			cout << "    ";
			GotoXY(x + 10, y);
			cout << "  ";
			GotoXY(x - 4, ++++y);
			cout << "  [";
			GotoXY(x + 10, y);
			cout << "]";
			Sleep(100);
		}
		break;
	case Key::SPACE:
		if (originY == y) return Menu::START;
		else if (originY + 2 == y) return Menu::INFO;
		else if (originY + 4 == y) return Menu::QUIT;
		break;
	}
	return Menu::FAIL;
}

void TitleScene::EnterAnimation()
{
	COORD resolution = GetConsoleResolution();
	int delayTime = 20;
	int flashCnt = 5;
	FlashAnimation(resolution, flashCnt, delayTime);
	CrossAnimation(resolution, delayTime);
	system("cls");
}

void TitleScene::FlashAnimation(COORD resolution, int cnt, int delayTime)
{
	for (int t = 0; t < cnt; ++t)
	{
		SetColor(COLOR::WHITE, COLOR::WHITE);
		system("cls");
		Sleep(delayTime);
		SetColor();
		system("cls");
		//	SetColor(COLOR::WHITE, COLOR::WHITE);
		//	for (int i = 0; i < resolution.Y; ++i)
		//	{
		//		for (int j = 0; j < resolution.X / 2; ++j)
		//		{
		//			cout << "  ";
		//		}
		//		cout << endl;
		//	}
		//	Sleep(delayTime);
		//	Gotoxy(0, 0);
		//	SetColor();
		//	for (int i = 0; i < resolution.Y; ++i)
		//	{
		//		for (int j = 0; j < resolution.X / 2; ++j)
		//		{
		//			cout << "  ";
		//		}
		//		cout << endl;
		//	}
	}
}

void TitleScene::CrossAnimation(COORD resolution, int delayTime)
{
	SetColor(COLOR::WHITE, COLOR::WHITE);
	for (int i = 0; i < resolution.X / 2; ++i)
	{
		for (int j = 0; j < resolution.Y; j += 2)
		{
			GotoXY(i * 2, j);
			cout << "  ";
		}
		for (int j = 1; j < resolution.Y; j += 2)
		{
			GotoXY(resolution.X - 2 - i * 2, j);
			cout << "  ";
		}
		Sleep(delayTime);
	}
	SetColor();
}
