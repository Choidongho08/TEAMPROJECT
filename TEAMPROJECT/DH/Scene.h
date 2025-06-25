#pragma once
#include "Enums.h"
#include "../Core/AsciiObject.h"

class Scene
{
public:
	SCENE Type;

protected:
	std::vector<AsciiObject>* asciiObjects;

public:
	Scene();
	virtual void SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects);
	virtual void Update();

private:

};

