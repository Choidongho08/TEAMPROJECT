#pragma once
#include "../DH/Enums.h";
#include "../DH/Scene.h";
#include "AsciiObject.h";
#include <Windows.h>;

class TitleScene : public Scene
{
public:
	COLOR textColor;
	COLOR bgColor;

	TitleScene();

	void Render();
	void Update() override;
	void SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects) override;

	Menu GetCurMenu();
	void EnterAnimation();
	void FrameBorderTraversalAnimation(COORD resolution, int delayTime);
};

