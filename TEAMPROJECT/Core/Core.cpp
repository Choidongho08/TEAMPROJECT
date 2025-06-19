#include "Core.h"

using std::vector;

Core* Core::Instance = nullptr;

Core::Core()
{
	Instance = this;

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
	
	// for (int i = 0; i < MAP_HEIGHT; ++i)
	// {
	//		gameMap[i] = new char[MAP_WIDTH];
	// }

	ChangeScene(Scene::TITLE);

	// return CORE{ titleScene, gameLogic, curScene, AsciiObjects };
}

void Core::Run()
{
	ReleaseAllSounds();

	while (true)
	{
		Update();
		Render();
		// FrameSync
		FrameSync(20);
	}
}

void Core::ChangeScene(Scene newScene)
{
	_curScene = newScene;

	switch (newScene)
	{
	case Scene::TITLE:
		_titleScene.Initialized(&_asciiObjects);
		break;
	case Scene::GAME:
		_gameLogic.Initialized(&_asciiObjects, &_gameMap);
		break;
	case Scene::INFO:
		_gameLogic.InfoScene();
		break;
	}
}

Scene Core::GetCurrentScene()
{
	return _curScene;
}

void Core::Update()
{
	while (_curScene != Scene::QUIT)
	{
		switch (_curScene)
		{
		case Scene::TITLE:
			_titleScene.Update();
			break;
		case Scene::GAME:
			_gameLogic.Update(); // curScene, gameMap, &player, &enemies);
			break;
		case Scene::INFO:
			_gameLogic.InfoScene();
			break;
		}
	}
}

void Core::Render()
{
}
