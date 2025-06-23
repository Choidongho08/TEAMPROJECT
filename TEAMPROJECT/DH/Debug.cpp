#include "Debug.h"
#include "../Core/Console.h"

Debug* Debug::Instance = nullptr;

Debug::Debug()
{
	x = y = 0;
	Instance = this;

	COORD resolution = GetConsoleResolution();
	x = resolution.X / 1.5 - 8;
	y = resolution.Y / 2;
	GotoXY(x, y++);
	cout << "-----------------------" << endl;
	GotoXY(x, y++);
	cout << "LOG";
	GotoXY(x, y++);
	cout << "-----------------------" << endl;
}

void Debug::Log(std::string string)
{
	GotoXY(x, y++);
	cout << string;
	GotoXY(0,0);
}
