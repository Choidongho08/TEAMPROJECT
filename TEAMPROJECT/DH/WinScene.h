#pragma once
#include "Scene.h"

class WinScene : public Scene
{
public:
private:
public:
	WinScene();
	~WinScene();

	void SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects) override;
	void Update() override;
private:
};

