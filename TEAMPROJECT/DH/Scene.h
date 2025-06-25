#pragma once
#include "Enums.h"

class Scene
{
public:
	SCENE Type;

private:

public:
	Scene();
	virtual void SceneInit(SCENE _type);
	virtual void Update();

private:

};

