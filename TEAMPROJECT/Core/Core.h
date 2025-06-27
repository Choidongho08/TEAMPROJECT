#pragma once
#include "GameLogic.h"
#include "TitleScene.h"
#include "../DH/InfoScene.h"
#include "../DH/DeadScene.h"
#include "../DH/WinScene.h"
#include "../JH/HEADER/ResultScene.h"
#include "AsciiObject.h"
#include "Mci.h"

class Core
{
public:
	static Core* Instance;

private:
	ResultScene _resultScene;
	TitleScene _titleScene;
	GameScene _gameScene;
	InfoScene _infoScene;
	WinScene _winScene;
	DeadScene _deadScene;
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

