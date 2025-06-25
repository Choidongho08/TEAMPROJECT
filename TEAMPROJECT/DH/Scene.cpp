#include "Scene.h"

Scene::Scene()
{
	Type = SCENE::TITLE;
	asciiObjects = nullptr;
}

void Scene::SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects)
{
	Type = _type;
	asciiObjects = _asciiObjects;
}

void Scene::Update()
{
}
