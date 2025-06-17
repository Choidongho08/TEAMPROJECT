#pragma once
#include "../DH/Enums.h";
#include "AsciiObject.h";
#include <Windows.h>;

class TitleScene
{
public:
	Scene* _pCurScene;
	vector<AsciiObject>* _objs;
	COLOR textColor;
	COLOR bgColor;

	TitleScene(Scene* pCurScene, vector<AsciiObject>* objs)
		: _pCurScene(pCurScene), _objs(objs)
	{

	}
	void Render();
	void Update();
	void Initialized();

	Menu GetCurMenu();
	void EnterAnimation();
	void FlashAnimation(COORD resolution, int cnt, int delayTime);
	void CrossAnimation(COORD resolution, int delayTime);
};

