#include "TitleScene.h"
#include<io.h>
#include<fcntl.h>
#include "../Core/Console.h"
#include "AsciiObject.h"
#include "KeyController.h"

void TitleScene::Render()
{
	COORD resolution = GetConsoleResolution();
	int y = resolution.Y / 5;
	Gotoxy(0, y);
	int coutmode = _setmode(_fileno(stdout), _O_U16TEXT);

	wcout << L"        ,--,                                                                             " << endl;
	wcout << L"      ,--.'|                             ,-.            ____                             " << endl;
	wcout << L"   ,--,  | :                         ,--/ /|          ,'  , `.                           " << endl;
	wcout << L",---.'|  : '                       ,--. :/ |       ,-+-,.' _ |                     ,---, " << endl;
	wcout << L"|   | : _' |                       :  : ' /     ,-+-. ;   , ||                 ,-+-. /  |" << endl;
	wcout << L":   : |.'  |    ,---.      ,---.   |  '  /     ,--.'|'   |  ||    ,--.--.     ,--.'|'   |" << endl;
	wcout << L"|   ' '  ; :   /     \    /     \  '  |  :    |   |  ,', |  |,   /       \   |   |  ,,' |" << endl;
	wcout << L"'   |  .'. |  /    /  |  /    / '  |  |   \   |   | /  | |--'   .--.  .-. |  |   | /  | |" << endl;
	wcout << L"|   | :  | ' .    ' / | .    ' /   '  : |. \  |   : |  | ,       \__\/: . .  |   | |  | |" << endl;
	wcout << L"'   : |  : ; '   ;   /| '   ; :__  |  | ' \ \ |   : |  |/        ,, .--.; |  |   | |  |/ " << endl;
	wcout << L"|   | '  ,/  '   |  / | '   | '.'| '  : |--'  |   | |`-'        /  /  ,.  |  |   | |--'  " << endl;
	wcout << L";   : ;--'   |   :    | |   :    : ;  |,'     |   ;/           ;  :   .'   \ |   |/      " << endl;
	wcout << L"|   ,/        \   \  /   \   \  /  '--'       '---'            |  ,     .-./ '---'       " << endl;
	wcout << L"'---'          `----'     `----'                                `--`---'                 " << endl;


	int wcoutmode = _setmode(_fileno(stdout), coutmode);
	int x = resolution.X / 3;
	y = resolution.Y / 3 * 2;
	Gotoxy(x, y);
	cout << "게임 시작";
	Gotoxy(x, y + 1);
	cout << "게임 정보";
	Gotoxy(x, y + 2);
	cout << "게임 종료";

}

void TitleScene::Update()
{
	for (auto obj : *_objs)
	{
		obj.ObjectUpdate();
		obj.ObjectRender(textColor, bgColor);
	}
	if (*_pCurScene != Scene::TITLE)
		return;

	Render();
	Sleep(30);

	Menu eMenu = GetCurMenu();
	switch (eMenu)
	{
	case Menu::START:
		EnterAnimation();
		*_pCurScene = Scene::GAME;
		break;
	case Menu::INFO:
		*_pCurScene = Scene::INFO;
		break;
	case Menu::QUIT:
		*_pCurScene = Scene::QUIT;
		break;
	}
	for (auto obj : *(_objs))
	{
		obj.ObjectUpdate();
	}
}

void TitleScene::Initialized()
{

}

Menu TitleScene::GetCurMenu()
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 3;
	static int y = resolution.Y / 3 * 2;
	static int originY = y;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::UP:
		if (y > originY)
		{
			Gotoxy(x - 2, y);
			cout << " ";
			Gotoxy(x - 2, --y);
			cout << ">";
			Sleep(100);
		}
		break;
	case Key::DOWN:
		if (y < originY + 2)
		{
			Gotoxy(x - 2, y);
			cout << " ";
			Gotoxy(x - 2, ++y);
			cout << ">";
			Sleep(100);
		}
		break;
	case Key::SPACE:
		if (originY == y) return Menu::START;
		else if (originY + 1 == y) return Menu::INFO;
		else if (originY + 2 == y) return Menu::QUIT;
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
			Gotoxy(i * 2, j);
			cout << "  ";
		}
		for (int j = 1; j < resolution.Y; j += 2)
		{
			Gotoxy(resolution.X - 2 - i * 2, j);
			cout << "  ";
		}
		Sleep(delayTime);
	}
	SetColor();
}
