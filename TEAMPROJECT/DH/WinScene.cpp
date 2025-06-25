#include "WinScene.h"

WinScene::WinScene()
{
}

WinScene::~WinScene()
{
}

void WinScene::SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects)
{
	Scene::SceneInit(_type, _asciiObjects);
}

void WinScene::Update()
{
	Scene::Update();
}
