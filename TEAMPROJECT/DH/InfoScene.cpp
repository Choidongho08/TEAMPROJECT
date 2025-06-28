#include "InfoScene.h"
#include "../Core/Core.h"

InfoScene::InfoScene()
{
}

InfoScene::~InfoScene()
{
}

void InfoScene::Update()
{

	Key key = KeyController();

	bool isQNow = (key == Key::Q);
	bool isENow = (key == Key::E);

	if (key == Key::ESC)
	{
		PlaySoundID(SOUNDID::CLICK);
		system("cls");
		Core::Instance->ChangeScene(SCENE::TITLE);
	}
	else if (isQNow && !wasQPressed)
	{
		PlaySoundID(SOUNDID::UPDOWN);
		system("cls");
		Render(true);
	}
	else if (isENow && !wasEPressed)
	{
		PlaySoundID(SOUNDID::UPDOWN);
		system("cls");
		Render(false);
	}

	wasQPressed = isQNow;
	wasEPressed = isENow;

	GotoXY(0, 0);
}

void InfoScene::SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects)
{
	SetCursorVisual(false, 50);

	Scene::SceneInit(_type, _asciiObjects);
	system("cls");
	Render(true);
}

void InfoScene::Render(bool isTrue)
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 2.5;
	int y = resolution.Y / 3;
	if (isTrue) {
		GotoXY(x, y++);
		cout << "=======================  ▶";
		GotoXY(x, y++);
		cout << "[    조작      방법   ]";
		GotoXY(x, y++);
		cout << "-----------------------";
		GotoXY(x, y);
		cout << " 조작키	: ↑ → ← ↓";
		GotoXY(x, y + 2);
		cout << " 스킬	: 스페이스바     ";
		GotoXY(x, y + 4);
		cout << " 다음 내용 보기 :  E   ";
		GotoXY(x, y + 5);
		cout << "=======================";
	}
	else {
		GotoXY(x - 4, y++);
		cout << "◀  ============================";
		GotoXY(x, y++);
		cout << "[      게임       방법     ]";
		GotoXY(x, y++);
		cout << "----------------------------";
		GotoXY(x, y);
		cout << "1. 적을 피해서 코인을 먹자";
		GotoXY(x, y + 2);
		cout << "2. 맵 곳곳에 아이템이 있다";
		GotoXY(x, y + 4);
		cout << "3. 아이템을 먹으면 스킬 획득";
		GotoXY(x, y + 6);
		cout << " - KILL  : 근처 적 제거";
		GotoXY(x, y + 8);
		cout << " - DASH  : 앞으로 대쉬";
		GotoXY(x, y + 10);
		cout << " - SIGHT : 시야 넓어짐 ";
		GotoXY(x, y + 12);
		cout << "   이전 내용 보기 : Q    ";
		GotoXY(x, y + 13);
		cout << "============================";
	}
}
