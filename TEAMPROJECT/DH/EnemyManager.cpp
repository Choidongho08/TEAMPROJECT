#include "EnemyManager.h"

void EnemyManager::SpawnEnemies(vector<Entity>& _entities)
{
	int enemyCnt = 0;
	for (POS pos : map->EnemySpawnPos)
	{
		Enemy newEnemy(*map);
		newEnemy.Initialize(pos, enemyCnt < map->MaxPlayerFollowingEnemyCnt);
		_entities.push_back(newEnemy);
		enemyCnt++;
	}
}
