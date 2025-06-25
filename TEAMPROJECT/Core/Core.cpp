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

	ChangeScene(SCENE::TITLE);

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

void Core::ChangeScene(SCENE newScene)
 {
	_curScene = newScene;

	switch (newScene)
	{
	case SCENE::TITLE:
		_titleScene.Initialized(&_asciiObjects);
		break;
	case SCENE::GAME:
		_gameScene.Initialized(&_asciiObjects, 2);
		break;
	case SCENE::INFO:
		_gameScene.InfoSceneInit();
		break;
	case SCENE::DEAD:
		_gameScene.DeadSceneInit();
		break;
	}
}

SCENE Core::GetCurrentScene()
{
	return _curScene;
}

void Core::Update()
{
	while (_curScene != SCENE::QUIT)
	{
		switch (_curScene)
		{
		case SCENE::TITLE:
			_titleScene.Update();
			break;
		case SCENE::GAME:
			_gameScene.Update();
			break;
		case SCENE::INFO:
			_gameScene.InfoScene();
		case SCENE::DEAD:
			break;
		}
	}
}

void Core::Render()
{
}
