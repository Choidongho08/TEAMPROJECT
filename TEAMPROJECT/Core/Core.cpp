#include "Core.h"

using std::vector;

void Core::Run()
{
	CORE core = Initialize();
	
	ReleaseAllSounds();

	while (true)
	{
		Update(core);
		Render();
		// FrameSync
		FrameSync(20);
	}
}

CORE Core::Initialize()
{
	vector<AsciiObject> AsciiObjects;

	vector<string> plane;
	plane.push_back("                    _                                      ");
	plane.push_back("                  -=\\`\\                                    ");
	plane.push_back("              |\\ ____\\_\\__                                 ");
	plane.push_back("            -=\\c`\"\"\"\"\"\"\" \"`)                               ");
	plane.push_back("               `~~~~~/ /~~`                                ");
	plane.push_back("                 -==/ /                                    ");
	plane.push_back("                   '-'                                     ");
		
	AsciiObject planeObj{ plane };

	AsciiObjects.push_back(planeObj);

	char** gameMap = new char* [MAP_HEIGHT];
	// for (int i = 0; i < MAP_HEIGHT; ++i)
	// {
	//		gameMap[i] = new char[MAP_WIDTH];
	// }

	Scene curScene;
	curScene = Scene::TITLE;

	TitleScene titleScene = { &curScene, &AsciiObjects };
	GameLogic gameLogic = { &AsciiObjects, gameMap, &curScene };

	gameLogic.Initialized();
	titleScene.Initialized();

	return CORE{ titleScene, gameLogic, curScene, AsciiObjects };
}

void Core::Update(CORE core)
{
	while (core.curScene != Scene::QUIT)
	{
		switch (core.curScene)
		{
		case Scene::TITLE:
			core.titleScene.Update();
			break;
		case Scene::GAME:
			core.gameLogic.Update(); // curScene, gameMap, &player, &enemies);
			break;
		case Scene::INFO:
			// InfoScene(curScene);
			break;
		}
	}
}

void Core::Render()
{
}
