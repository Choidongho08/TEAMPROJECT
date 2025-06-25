#pragma once
#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class EnemyManager
{
public:
	std::vector<Enemy> Enemies;

private:
	AStar aStar;
	Map* map;

public:
	EnemyManager(Map* _map) : aStar(*_map), map(_map) {}

	void SpawnEnemies(vector<Entity*>* _entities, Player* player);
	void DeadEnemy(const Enemy& enemy);
private:
};

