#pragma once
#include "GameLogic.h"
#include "TitleScene.h"
#include "AsciiObject.h"
#include "Mci.h"

class Core
{
public:
	static Core* Instance;

private:
	TitleScene _titleScene;
	GameLogic _gameLogic;
	Scene _curScene;
	vector<AsciiObject> _asciiObjects;

public:
	Core();
	~Core() { delete Instance; }

	void Run();
	void ChangeScene(Scene newScene);
	Scene GetCurrentScene();

private:
	void Update();
	void Render();
};

