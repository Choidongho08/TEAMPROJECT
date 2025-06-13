#include "../DH/GameLogic.h"
#include "../DH/TitleScene.h"
#include "../DH/AsciiObject.h"
#include "Mci.h"
#include<iostream>

int main()
{
	Scene curScene = Scene::TITLE;
	AsciiObjcets objs;
	char gameMap[MAP_HEIGHT][MAP_WIDTH] = {};
	Player player = {};
	vector<Enemy> enemies = {};
	Init(objs, gameMap, &player);
	while (curScene != Scene::QUIT)
	{
		switch (curScene)
		{
		case Scene::TITLE:
			TitleScene(curScene, objs);
			break;
		case Scene::GAME:
			GameScene(curScene, gameMap, &player, &enemies);
			break;
		case Scene::INFO:
			InfoScene(curScene);
			break;
		}
	}
	ReleaseAllSounds();
}