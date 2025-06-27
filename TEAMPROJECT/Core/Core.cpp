#include "Core.h"

using std::vector;

Core* Core::Instance = nullptr;

Core::Core()
{
	Instance = this;

	// vector<AsciiObject> AsciiObjects;
	// 
	// vector<string> plane;
	// plane.push_back("                    _                                      ");
	// plane.push_back("                  -=\\`\\                                    ");
	// plane.push_back("              |\\ ____\\_\\__                                 ");
	// plane.push_back("            -=\\c`\"\"\"\"\"\"\" \"`)                               ");
	// plane.push_back("               `~~~~~/ /~~`                                ");
	// plane.push_back("                 -==/ /                                    ");
	// plane.push_back("                   '-'                                     ");
	// 
	// AsciiObject planeObj{ plane };
	// 
	// AsciiObjects.push_back(planeObj);
	
	// for (int i = 0; i < MAP_HEIGHT; ++i)
	// {
	//		gameMap[i] = new char[MAP_WIDTH];
	// }


	// return CORE{ titleScene, gameLogic, curScene, AsciiObjects };
}

void Core::Run()
{

	ReleaseAllSounds();

	if (!InitAllSounds()) return;

	ChangeScene(SCENE::TITLE);

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
	switch (newScene)
	{
	case SCENE::TITLE:
		_titleScene.SceneInit(newScene, &_asciiObjects);
		break;
	case SCENE::GAME:
		_gameScene.SceneInit(newScene, &_asciiObjects);
		break;
	case SCENE::INFO:
		_infoScene.SceneInit(newScene, &_asciiObjects);
		break;
	case SCENE::QUIT:
		break;
	case SCENE::WIN:
		_winScene.SceneInit(newScene, &_asciiObjects);
		break;
	case SCENE::END:
		break;
	case SCENE::DEAD:
		_deadScene.SceneInit(newScene, &_asciiObjects);
		break;
	}

	_curScene = newScene;
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
			_infoScene.Update();
			break;
		case SCENE::QUIT:
			break;
		case SCENE::WIN:
			_winScene.Update();
			break;
		case SCENE::END:
			break;
		case SCENE::DEAD:
			_deadScene.Update();
			break;
		}
	}
}

void Core::Render()
{
}
