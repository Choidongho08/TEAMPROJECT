#pragma once
#include "Scene.h"
#include "../Core/Console.h"
#include "../Core/KeyController.h"

class InfoScene : public Scene
{
public:
private:
	bool wasQPressed = false;
	bool wasEPressed = false;

public:
	InfoScene();
	~InfoScene();

	void Update() override;
	void SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects) override;
	void Render(bool isTrue);
private:
};