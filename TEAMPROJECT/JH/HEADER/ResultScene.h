#include "../../DH/Scene.h"
#include "../../Core/Console.h"
#include "../../Core/KeyController.h"
#include "../../DH/PlayerManager.h"
#pragma once
class ResultScene : public Scene
{
private:
	//PlayerManager PlayerManager;

public:
	ResultScene();
	~ResultScene();
	void SceneInit(SCENE _type, std::vector<AsciiObject>* _asciiObjects) override;

	Menu GetCurMenu();
	void Update() override;
	void Render(int score);
	void RenderGameOver();
	void RenderClear();
};

