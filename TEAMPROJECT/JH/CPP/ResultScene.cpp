#include "../HEADER/ResultScene.h"
#include "../../Core/Core.h"
#include "../../Core/KeyController.h"
#include<io.h>
#include<fcntl.h>

ResultScene::ResultScene()
{
	
}

ResultScene::~ResultScene()
{

}

void ResultScene::SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects)
{
	SetCursorVisual(false, 50);

	Sleep(100);

	system("cls");

    if (_type == SCENE::DEAD) {
		PlaySoundID(SOUNDID::GAMEOVER);
        RenderGameOver();
    }
    else if (_type == SCENE::WIN) {
		PlaySoundID(SOUNDID::GAMEWIN);
        RenderClear();
    }

	Render();
}

Menu ResultScene::GetCurMenu()
{
	COORD resolution = GetConsoleResolution();
	static const int originX = (resolution.X - 5) / 2 +20;
	static int x = originX;

	int y = (resolution.Y - 11) / 2 + 11;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::LEFT:
		PlaySoundID(SOUNDID::UPDOWN);
		if (x > originX - 20)
		break;
	case Key::RIGHT:
		PlaySoundID(SOUNDID::UPDOWN);
		break;
	case Key::SPACE:
		PlaySoundID(SOUNDID::CLICK);

		if (originX == x) return Menu::QUIT;
	}
	return Menu::FAIL;
}

void ResultScene::Update()
{
	Sleep(30);

	Menu eMenu = GetCurMenu();
	switch (eMenu)
	{
		case Menu::TITLE:
		system("cls");
		Core::Instance->ChangeScene(SCENE::TITLE);
		break;
	case Menu::QUIT:
		Core::Instance->ChangeScene(SCENE::QUIT);
		break;
	}
}

void ResultScene::Render()
{
	COORD resolution = GetConsoleResolution();
	int originX = (resolution.X - 5) / 2;
	int y = (resolution.Y - 11) / 2 + 11;

	GotoXY(originX , y);
	cout << "게임 종료";

	GotoXY(originX - 4, y);
	cout << "  [";
	GotoXY(originX + 9, y);
	cout << " ]";
	GotoXY(originX + 4, y + 2);
	cout << "↑";
	GotoXY(originX - 3, y + 4);
	cout << "스페이스바로 선택";
}

void ResultScene::RenderGameOver()
{
    COORD resolution = GetConsoleResolution();
    int x = (resolution.X / 7);
    int y = (resolution.Y / 6);
    int coutmode = _setmode(_fileno(stdout), _O_U16TEXT);

    GotoXY(x, ++y); wcout << L"	▄▀▀▀▀▄    ▄▀▀█▄   ▄▀▀▄ ▄▀▄  ▄▀▀█▄▄▄▄      ▄▀▀▀▀▄   ▄▀▀▄ ▄▀▀▄  ▄▀▀█▄▄▄▄  ▄▀▀▄▀▀▀▄ ";
    GotoXY(x, ++y); wcout << L"	█         ▐ ▄▀ ▀▄ █  █ ▀  █ ▐  ▄▀   ▐     █      █ █   █    █ ▐  ▄▀   ▐ █   █   █";
    GotoXY(x, ++y); wcout << L"	█    ▀▄▄    █▄▄▄█ ▐  █    █   █▄▄▄▄▄      █      █ ▐  █    █    █▄▄▄▄▄  ▐  █▀▀█▀ ";
    GotoXY(x, ++y); wcout << L"	█     █ █  ▄▀   █   █    █    █    ▌      ▀▄    ▄▀    █   ▄▀    █    ▌   ▄▀    █ ";
    GotoXY(x, ++y); wcout << L"	▐▀▄▄▄▄▀ ▐ █   ▄▀  ▄▀   ▄▀    ▄▀▄▄▄▄         ▀▀▀▀       ▀▄▀     ▄▀▄▄▄▄   █     █  ";
    GotoXY(x, ++y); wcout << L"	▐         ▐   ▐   █    █     █    ▐                            █    ▐   ▐     ▐  ";

    int wcoutmode = _setmode(_fileno(stdout), coutmode);
}

void ResultScene::RenderClear()
{
    COORD resolution = GetConsoleResolution();
    int x = (resolution.X / 3.7);
    int y = (resolution.Y / 6) - 2;
    int coutmode = _setmode(_fileno(stdout), _O_U16TEXT);

    GotoXY(x, ++y); wcout << L" _______  _______  _______  _______            _________ _       ";
    GotoXY(x, ++y); wcout << L"(  ____ \\(  ___  )(       )(  ____ \\  |\\     /|\\__   __/( (    /|";
    GotoXY(x, ++y); wcout << L"| (    \\/| (   ) || () () || (    \\/  | )   ( |   ) (   |  \\  ( |";
    GotoXY(x, ++y); wcout << L"| |      | (___) || || || || (__      | | _ | |   | |   |   \\ | |";
    GotoXY(x, ++y); wcout << L"| | ____ |  ___  || |(_)| ||  __)     | |( )| |   | |   | (\\ \\) |";
    GotoXY(x, ++y); wcout << L"| | \\_  )| (   ) || |   | || (        | || || |   | |   | | \\   |";
    GotoXY(x, ++y); wcout << L"| (___) || )   ( || )   ( || (____/\\  | () () |___) (___| )  \\  |";
    GotoXY(x, ++y); wcout << L"(_______)|/     \\||/     \\|(_______/  (_______)\\_______/|/    )_)";

    int wcoutmode = _setmode(_fileno(stdout), coutmode);
}
