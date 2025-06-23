#pragma once
#include "Map.h"
#include "Player.h"

class PlayerManager
{
public:
	Player player;

private:
	Map* map;

public:
	PlayerManager(Map* _map) : map(_map) {}
	void SpawnPlayer(vector<Entity>& entities);

private:
};

