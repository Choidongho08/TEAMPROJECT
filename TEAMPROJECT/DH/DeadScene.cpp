#include "DeadScene.h"

DeadScene::DeadScene()
{
}

DeadScene::~DeadScene()
{
}

void DeadScene::SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects)
{
	Scene::SceneInit(_type, _asciiObjects);
}

void DeadScene::Update()
{
	Scene::Update();
}
