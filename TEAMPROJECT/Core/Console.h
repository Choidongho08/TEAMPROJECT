#pragma once
#include<iostream>
//using namespace std;
using std::cout;
using std::wcout;
using std::endl;
#include<string>
using std::string;
using std::wstring;
//#include<vector>
//using std::vector;
#include<Windows.h>

void SetConsoleSettings(int _width, int _height, bool _isFullscreen, const std::wstring& _title);
void SetLockResize();
COORD GetConsoleResolution();


void Gotoxy(int _x, int _y);
BOOL IsGotoxy(int _x, int _y);
COORD CursorPos();
void SetCursorVisual(bool _isVis, DWORD _size);
enum class COLOR
{
	BLACK, BLUE, GREEN, SKYBLUE, RED,
	VOILET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
	LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
	LIGHT_YELLOW, WHITE, END
};
int Random();
int Random(int extra, int extra2);
void SetColor(COLOR _textcolor = COLOR::WHITE, COLOR _bgcolor = COLOR::BLACK);
void FrameSync(unsigned int frame);

void SetConsoleFont(LPCWSTR fontName, COORD _size, UINT _weight);
