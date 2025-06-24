#include "EnemyManager.h"

void EnemyManager::SpawnEnemies(vector<Entity*>* _entities, Player* player)
{
	int enemyCnt = 0;
	for (POS pos : map->EnemySpawnPos)
	{
		Enemy newEnemy(*map);
		newEnemy.Initialize(pos, enemyCnt < map->MaxPlayerFollowingEnemyCnt);
		newEnemy.PPlayer = player;
		Enemies.push_back(newEnemy);
		enemyCnt++;
	}
	for (auto& enemy : Enemies)
	{
		_entities->push_back(&enemy);
	}
}
