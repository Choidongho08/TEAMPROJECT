#include "AsciiObject.h"
#include "../Core/Console.h"

void ObjectInit(AsciiObjcets& objs)
{
	objs.vecPlane =
	{
		"                    _                                      ",
			"                  -=\\`\\                                    ",
			"              |\\ ____\\_\\__                                 ",
			"            -=\\c`\"\"\"\"\"\"\" \"`)                               ",
			"               `~~~~~/ /~~`                                ",
			"                 -==/ /                                    ",
			"                   '-'                                     "
	};
	objs.vecCloud =
	{
		"                  _  _                                     ",
			"                 ( `   )_                                  ",
			"                (    )    `)                               ",
			"              (_   (_ .  _) _)                             "
	};
}

void ObjectUpdate(AsciiObjcets& objs)
{
	// for���� 3���� ��� �ε��̹�� - ������ó��
	// ���� �ű��
	//for (int i = 0; i < objs.vecCloud.size(); ++i)
	//	std::rotate(objs.vecCloud.begin(),
	//		objs.vecCloud.begin() + 1,
	//		objs.vecCloud.end());
	// ���ͷ����� ���
	//for (auto it = objs.vecCloud.begin(); it != objs.vecCloud.end(); ++it)
	//{
	//	auto& line = *it;
	//}
	// ������� for��
	for (string& line : objs.vecCloud)
	{
		std::rotate(line.begin(), line.begin() + 1, line.end());
	}
	for (string& line : objs.vecPlane)
	{
		std::rotate(line.rbegin(), line.rbegin() + 1, line.rend());
	}
	
}

void ObjectRender(const AsciiObjcets& objs)
{
	// �׷���

	int cloudCnt = objs.vecCloud.size();
	int planeCnt = objs.vecPlane.size();
	SetColor(COLOR::LIGHT_BLUE, COLOR::BLACK);
	for (int i = 0; i < planeCnt; ++i)
	{
		Gotoxy(0, i);
		cout << objs.vecPlane[i];
	}
	SetColor(COLOR::GREEN, COLOR::BLACK);
	for (int i = 0; i < cloudCnt; ++i)
	{
		Gotoxy(0, i + planeCnt);
		cout << objs.vecCloud[i];
	}
	SetColor();
}
