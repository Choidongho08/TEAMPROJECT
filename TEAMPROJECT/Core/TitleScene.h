#pragma once
#include "../DH/Enums.h";
#include "AsciiObject.h";
#include <Windows.h>;

class TitleScene
{
public:
	vector<AsciiObject>* _pObjs;
	COLOR textColor;
	COLOR bgColor;

	TitleScene();

	void Render();
	void Update();
	void Initialized(vector<AsciiObject>* objs);

	Menu GetCurMenu();
	void EnterAnimation();
	void FlashAnimation(COORD resolution, int cnt, int delayTime);
	void CrossAnimation(COORD resolution, int delayTime);
};

