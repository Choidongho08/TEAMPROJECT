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
		cout << "=======================  ��";
		GotoXY(x, y++);
		cout << "[    ����      ���   ]";
		GotoXY(x, y++);
		cout << "-----------------------";
		GotoXY(x, y);
		cout << " ����Ű	: �� �� �� ��";
		GotoXY(x, y + 2);
		cout << " ��ų	: �����̽���     ";
		GotoXY(x, y + 4);
		cout << " ���� ���� ���� :  E   ";
		GotoXY(x, y + 5);
		cout << "=======================";
	}
	else {
		GotoXY(x - 4, y++);
		cout << "��  ============================";
		GotoXY(x, y++);
		cout << "[      ����       ���     ]";
		GotoXY(x, y++);
		cout << "----------------------------";
		GotoXY(x, y);
		cout << "1. ���� ���ؼ� ������ ����";
		GotoXY(x, y + 2);
		cout << "2. �� ������ �������� �ִ�";
		GotoXY(x, y + 4);
		cout << "3. �������� ������ ��ų ȹ��";
		GotoXY(x, y + 6);
		cout << " - KILL  : ��ó �� ����";
		GotoXY(x, y + 8);
		cout << " - DASH  : ������ �뽬";
		GotoXY(x, y + 10);
		cout << " - SIGHT : �þ� �о��� ";
		GotoXY(x, y + 12);
		cout << "   ���� ���� ���� : Q    ";
		GotoXY(x, y + 13);
		cout << "============================";
	}
}
