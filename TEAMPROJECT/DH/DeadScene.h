#pragma once
#include "Scene.h"

class DeadScene : public Scene
{
public:
private:
public:
	DeadScene();
	~DeadScene();

	void SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects) override;
	void Update() override;
private:
};

