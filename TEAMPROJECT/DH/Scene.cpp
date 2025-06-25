#include "Scene.h"

Scene::Scene()
{
	Type = SCENE::TITLE;
}

void Scene::SceneInit(SCENE _type)
{
	Type = _type;
}

void Scene::Update()
{
}
