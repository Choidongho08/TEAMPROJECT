#pragma once
#include "GameLogic.h"
#include "TitleScene.h"
#include "AsciiObject.h"
#include "Mci.h"

struct CORE
{
	TitleScene titleScene;
	GameLogic gameLogic;
	Scene curScene;
	vector<AsciiObject> AsciiObjects;
};

class Core
{
public:
private:

public:
	void Run();
	CORE Initialize();

private:
	void Update(CORE core);
	void Render();
};

