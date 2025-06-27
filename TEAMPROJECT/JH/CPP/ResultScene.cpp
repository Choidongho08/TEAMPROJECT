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
	system("cls");
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 2.5;
	int y = resolution.Y / 3 * 2;
	GotoXY(x - 4, y);
	cout << "  [";
	GotoXY(x + 10, y);
	cout << "]  ← 스페이스바로 선택";

	Render(1);

	if (_type == SCENE::DEAD) {
		//PlaySoundID(_type, true);
		RenderGameOver();
	}
	else if (_type == SCENE::WIN) {
		//PlaySoundID(_type, true);
		RenderClear();
	}
}

Menu ResultScene::GetCurMenu()
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 2.5;
	static int y = resolution.Y / 3 * 2;
	static int originY = y;
	Key eKey = KeyController();
	switch (eKey)
	{
	case Key::UP:
		PlaySoundID(SOUNDID::UPDOWN);
		if (y > originY)
		{
			GotoXY(x - 5, y);
			cout << "    ";
			GotoXY(x + 10, y);
			cout << "                       ";
			GotoXY(x - 4, ----y);
			cout << "  [";
			GotoXY(x + 10, y);
			cout << "]  ← 스페이스바로 선택";
			Sleep(100);
		}
		break;
	case Key::DOWN:
		PlaySoundID(SOUNDID::UPDOWN);
		if (y < originY + 2)
		{
			GotoXY(x - 5, y);
			cout << "    ";
			GotoXY(x + 10, y);
			cout << "                       ";
			GotoXY(x - 4, ++++y);
			cout << "  [";
			GotoXY(x + 10, y);
			cout << "]  ← 스페이스바로 선택";
			Sleep(100);
		}
		break;
	case Key::SPACE:
		PlaySoundID(SOUNDID::CLICK);

		if (originY == y) return Menu::TITLE;
		else if (originY + 2 == y) return Menu::QUIT;
		break;
	}
	return Menu::FAIL;
	return Menu();
}

void ResultScene::Update() {


	if (Core::Instance->GetCurrentScene() != SCENE::END)
		return;

	Sleep(30);

	Menu eMenu = GetCurMenu();
	switch (eMenu)
	{
	case Menu::TITLE:
		Core::Instance->ChangeScene(SCENE::TITLE);
		Sleep(100);
		break;
	case Menu::QUIT:
		Core::Instance->ChangeScene(SCENE::QUIT);
		break;
	}
}

void ResultScene::Render(int score)
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 2.5;
	int y = resolution.Y / 3 * 2;
	GotoXY(x, y);
	cout << "메인 메뉴";
	GotoXY(x, y + 2);
	cout << "게임 종료";
}

void ResultScene::RenderGameOver()
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 11;
	int y = resolution.Y / 7;
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
	int x = resolution.X / 4.5;
	int y = resolution.Y / 7;
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
