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

    Render(1);
    if (_type == SCENE::DEAD) {
        RenderGameOver();
    }
    else if (_type == SCENE::WIN) {
        RenderClear();
    }
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
		{
			GotoXY(x + 3, y + 2);
			cout << "    ";
			GotoXY(x - 3, y + 4);
			cout << "                 ";
			GotoXY(x - 5, y);
			cout << "    ";
			GotoXY(x + 10, y);
			cout << "    ";

			x -= 40;

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
		if (x < originX)
		{
			GotoXY(x + 3, y + 2);
			cout << "    ";
			GotoXY(x - 3, y + 4);
			cout << "                 ";
			GotoXY(x - 5, y);
			cout << "    ";
			GotoXY(x + 10, y);
			cout << "    ";

			x += 40;

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

		if (originX - 40 == x) return Menu::TITLE;
		else if (originX == x) return Menu::QUIT;
		break;
	}
	return Menu::FAIL;
}

void ResultScene::Update()
{
	if (Core::Instance->GetCurrentScene() != SCENE::END)
		return;

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

void ResultScene::Render(int score)
{
	COORD resolution = GetConsoleResolution();
	int originX = (resolution.X - 5) / 2;
	int y = (resolution.Y - 11) / 2 + 11;

	GotoXY(originX - 20, y);
	cout << "메인 메뉴";

	GotoXY(originX + 20, y);
	cout << "게임 종료";

	originX += 20;

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
