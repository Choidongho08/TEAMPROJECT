#pragma once
#include "GameLogic.h"
#include "TitleScene.h"
#include "../DH/InfoScene.h"
#include "AsciiObject.h"
#include "Mci.h"

class Core
{
public:
	static Core* Instance;

private:
	TitleScene _titleScene;
	GameScene _gameScene;
	InfoScene _infoScene;
	SCENE _curScene;
	vector<AsciiObject> _asciiObjects;

public:
	Core();
	~Core() { delete Instance; }

	void Run();
	void ChangeScene(SCENE newScene);
	SCENE GetCurrentScene();

private:
	void Update();
	void Render();
};

