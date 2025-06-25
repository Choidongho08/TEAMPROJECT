#pragma once
#include "../DH/Enums.h";
#include "../DH/Scene.h";
#include "AsciiObject.h";
#include <Windows.h>;

class TitleScene : public Scene
{
public:
	vector<AsciiObject>* _pObjs;
	COLOR textColor;
	COLOR bgColor;

	TitleScene();

	void Render();
	void Update() override;
	void Initialized(vector<AsciiObject>* objs);

	Menu GetCurMenu();
	void EnterAnimation();
	void FrameBorderTraversalAnimation(COORD resolution, int delayTime);
};

