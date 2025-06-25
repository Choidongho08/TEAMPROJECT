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
		Core::Instance->ChangeScene(SCENE::TITLE);
		system("cls");
	}
	else if (isQNow && !wasQPressed)
	{
		system("cls");
		Render(true);
	}
	else if (isENow && !wasEPressed)
	{
		system("cls");
		Render(false);
	}

	wasQPressed = isQNow;
	wasEPressed = isENow;

	GotoXY(0, 0);
}

void InfoScene::SceneInit(SCENE type)
{
	Scene::SceneInit(type);
	system("cls");
	Render(true);
}

void InfoScene::Render(bool isTrue)
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 3;
	int y = resolution.Y / 3;
	if (isTrue) {
		GotoXY(x, y++);
		cout << "=======================  ��";
		GotoXY(x, y++);
		cout << "[    ����      ���   ]";
		GotoXY(x, y++);
		cout << "-----------------------";
		GotoXY(x, y++);
		cout << " ����Ű	: �� �� �� ��";
		GotoXY(x, y++);
		cout << " ��ų	: �����̽���     ";
		GotoXY(x, y++);
		cout << " ���� ���� ���� :  E   ";
		GotoXY(x, y++);
		cout << "=======================";
	}
	else {
		GotoXY(x - 4, y++);
		cout << "��  ==========================";
		GotoXY(x, y++);
		cout << " [    ����      ���   ]";
		GotoXY(x, y++);
		cout << "--------------------------";
		GotoXY(x, y++);
		cout << "1. ���� ���ؼ� ������ ����";
		GotoXY(x, y++);
		cout << "2. �� ������ �������� �ִ�";
		GotoXY(x, y++);
		cout << "3. �������� ������ ��ų ȹ��";
		GotoXY(x, y++);
		cout << " - KILL  : ��ó �� ����";
		GotoXY(x, y++);
		cout << " - DASH  : ������ �뽬";
		GotoXY(x, y++);
		cout << " - SIGHT : �þ� �о��� ";
		GotoXY(x, y++);
		cout << " ���� ���� ���� : Q    ";
		GotoXY(x, y++);
		cout << "==========================";
	}
}
