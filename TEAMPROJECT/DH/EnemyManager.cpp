#include "EnemyManager.h"

void EnemyManager::SpawnEnemies(vector<Entity*>* _entities)
{
	int enemyCnt = 0;
	for (POS pos : map->EnemySpawnPos)
	{
		Enemy newEnemy(*map);
		newEnemy.Initialize(pos, enemyCnt < map->MaxPlayerFollowingEnemyCnt);
		Enemies.push_back(newEnemy);
		enemyCnt++;
	}
	for (auto& enemy : Enemies)
	{
		_entities->push_back(&enemy);
	}
}
