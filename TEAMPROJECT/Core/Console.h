#pragma once
#include<iostream>
#include<string>
#include<Windows.h>

using std::cout;
using std::endl;
using std::string;
using std::wstring;


void SetConsoleSettings(int _width, int _height, bool _isFullscreen, const std::wstring& _title);
void SetLockResize();
COORD GetConsoleResolution();


void GotoXY(int _x, int _y);
BOOL IsGotoXY(int _x, int _y);
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
void COUT(string s);
