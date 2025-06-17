#include <Windows.h>
#include "KeyController.h"

Key KeyController()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		//Sleep(100);
		return Key::UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		//Sleep(100);
		return Key::DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		//Sleep(60);
		return Key::LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		//Sleep(60);
		return Key::RIGHT;
	}
	// if (GetAsyncKeyState('W') & 0x8000)
	// {
	// 	Sleep(60);
	// 	return Key::W;
	// }
	// if (GetAsyncKeyState('E') & 0x8000)
	// {
	// 	Sleep(60);
	// 	return Key::E;
	// }
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		//Sleep(100);
		return Key::SPACE;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		Sleep(60);
		return Key::ESC;
	}
	
	return Key::FAIL;
}