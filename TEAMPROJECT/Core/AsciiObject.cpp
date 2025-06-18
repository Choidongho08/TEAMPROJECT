#include "AsciiObject.h"
#include "../Core/Console.h"


void AsciiObject::ObjectInit()
{
}

void AsciiObject::ObjectUpdate()
{
	for (string& line : obj)
	{
		std::rotate(line.begin(), line.begin() + 1, line.end());
	}
}

void AsciiObject::ObjectRender(COLOR txtColor, COLOR bgColor)
{
	int objCnt = obj.size();
	SetColor(txtColor, bgColor);
	for (int i = 0; i < objCnt; ++i)
	{
		Gotoxy(0, i);
		cout << obj[i];
	}
	SetColor();
}
