﻿#include "TitleScene.h"
#include<io.h>
#include<fcntl.h>
#include "../Core/Console.h"
#include "AsciiObject.h"
#include "KeyController.h"
#include "Core.h"

TitleScene::TitleScene()
{
	textColor = COLOR::WHITE;
	bgColor = COLOR::BLACK;
}

void TitleScene::SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects)
{
	SetCursorVisual(false, 50);

	COORD resolution = GetConsoleResolution();
	int x = (resolution.X - 5) / 2;
    int y = (resolution.Y - 11) / 2 + 11;
	GotoXY(x - 4, y);
	cout << "  [";
	GotoXY(x + 9, y);
	cout << " ]";
	GotoXY(x + 4, y + 2);
	cout << "↑";
	GotoXY(x - 3, y + 4);
	cout << "스페이스바로 선택";

	asciiObjects = _asciiObjects;
	textColor = COLOR::WHITE;
	bgColor = COLOR::BLACK;

	Render();

	PlaySoundID(SOUNDID::TITLE, true);
}

void TitleScene::Render()
{
	COORD resolution = GetConsoleResolution();
	int x = (resolution.X - 90) / 2;
	int y = (resolution.Y - 11) / 3.5;

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
	x = (resolution.X - 5) / 2;
	y = y + 7;
	GotoXY(x - 20, y);
	cout << "게임 시작";
	GotoXY(x, y);  
	cout << "게임 정보";
	GotoXY(x + 20, y);
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
	
	if (Core::Instance->GetCurrentScene() != SCENE::TITLE)
		return;

	Sleep(30);

	Menu eMenu = GetCurMenu();
	switch (eMenu)
	{
	case Menu::START:
		EnterAnimation();
		Core::Instance->ChangeScene(SCENE::GAME);
		break;
	case Menu::INFO:
		Core::Instance->ChangeScene(SCENE::INFO);
		break;
	case Menu::QUIT:
		Core::Instance->ChangeScene(SCENE::QUIT);
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
	static const int originX = (resolution.X - 5) / 2;
	static int x = originX;

	int y = (resolution.Y - 11) / 2 +11;
	Key eKey = KeyController();

	switch (eKey)
	{
	case Key::LEFT:
		PlaySoundID(SOUNDID::UPDOWN);
		if (x > originX - 20)
		{
			GotoXY(x + 3, y + 2);
			cout << "    ";
			GotoXY(x - 3, y + 4);
			cout << "                 ";
			GotoXY(x - 5, y);
			cout << "    ";
			GotoXY(x + 10, y);
			cout << "    ";

			x -= 20;

			GotoXY(x - 4, y);
			cout << "  [";
			GotoXY(x + 9, y);
			cout << " ]";
			GotoXY(x + 4, y + 2);
			cout << "↑";
			GotoXY(x - 3, y + 4);
			cout << "스페이스바로 선택";
			Sleep(100);
		}
		break;
	case Key::RIGHT:
		PlaySoundID(SOUNDID::UPDOWN);
		if (x < originX + 20)
		{
			GotoXY(x + 3, y + 2);
			cout << "    ";
			GotoXY(x - 3, y + 4);
			cout << "                 ";
			GotoXY(x - 5, y);
			cout << "    ";
			GotoXY(x + 10, y);
			cout << "    ";

			x += 20;

			GotoXY(x - 4, y);
			cout << "  [";
			GotoXY(x + 9, y);
			cout << " ]";
			GotoXY(x + 4, y + 2);
			cout << "↑";
			GotoXY(x - 3, y + 4);
			cout << "스페이스바로 선택";
			Sleep(100);
		}
		break;
	case Key::SPACE:
		PlaySoundID(SOUNDID::CLICK);

		if (originX - 20 == x) return Menu::START;
		else if (originX == x) {
			y -= 2;
			return Menu::INFO;
		}
		else if (originX + 20 == x) return Menu::QUIT;
		break;
	}
	return Menu::FAIL;
}


void TitleScene::EnterAnimation()
{
	COORD resolution = GetConsoleResolution();
	int delayTime = 20;
	int flashCnt = 5;
	FrameBorderTraversalAnimation(resolution, delayTime);
	system("cls");
}

void TitleScene::FrameBorderTraversalAnimation(COORD resolution, int delayTime)
{
	PlaySoundID(SOUNDID::GAMESTART);

	SetColor(COLOR::WHITE, COLOR::WHITE);
	int left = 0, top = 0;
	int right = resolution.X;
	int bottom = resolution.Y;

	while (left <= right && top <= bottom)
	{
		for (int x = left; x <= right; x += 2) {
			GotoXY(x, top);
			cout << "  ";
		}
		Sleep(delayTime);

		for (int y = top; y <= bottom; ++y) {
			GotoXY(right, y);
			cout << "  ";
		}
		Sleep(delayTime);

		for (int x = right; x >= left; x -= 2) {
			GotoXY(x, bottom);
			cout << "  ";
		}
		Sleep(delayTime);

		for (int y = bottom; y > top; --y) {
			GotoXY(left, y);
			cout << "  ";
		}
		Sleep(delayTime);

		left += 2;
		top++;
		right -= 2;
		bottom--;
	}
	SetColor();
	StopSound(SOUNDID::TITLE);
}