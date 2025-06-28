#include "EnemyManager.h"
#include "../Core/Console.h"

void EnemyManager::SpawnEnemies(vector<Entity*>& _entities, Player* player)
{
	int enemyCnt = 0;
	for (POS pos : map->EnemySpawnPos)
	{
		Enemy newEnemy(map);
		newEnemy.Initialize(EnemyState{ true, enemyCnt < map->MaxPlayerFollowingEnemyCnt }, pos, enemyCnt);
		newEnemy.pPlayer = player;
		newEnemy.aStarDuration = enemyCnt + 2; 
		Enemies.push_back(newEnemy);
		enemyCnt++;
	}
	for (auto& enemy : Enemies)
	{
		_entities.push_back(&enemy);
	}
}

void EnemyManager::DeadEnemy(const Enemy& enemy)
{
	std::vector<Enemy>::iterator iter = std::find(Enemies.begin(), Enemies.end(), enemy);
	if (iter != Enemies.end())
	{
		iter->state.isAlive = false;
	}
}

void EnemyManager::DeadEnemy2(POS deadPos)
{
	for (auto& enemy : Enemies)
	{
		if (enemy.pos.tPos == deadPos)
		{
			enemy.state.isAlive = false;
			break;
		}
	}
}


