#include "Map.h"
#include "../Core/Console.h"
#include <cmath>

void Map::InitializeMap(const vector<vector<Node>>& _grid)
{
	MaxItemCnt = Random(3, 3);
	grid = _grid;

	for (const vector<Node>& row : _grid)
	{
		for (const Node& col : row)
		{
			if (col.tile == (int)Tile::PLAYER_START)
				PlayerSpawnPos = col.pos;
			if (col.tile == (int)Tile::ENEMY_SPAWN)
			{
				EnemySpawnPos.push_back(col.pos);
				MaxPlayerFollowingEnemyCnt++;
			}
			if (col.tile == (int)Tile::ITEM)
				MaxItemCnt++;
			if (col.tile == (int)Tile::COIN)
				MapCoinCnt++;
		}
	}
}

void Map::Render(const int& x, const int& y, const int& distance)
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			int dx = j - x;
			int dy = i - y;
			if (dx * dx + dy * dy <= distance * distance)
			{
				if (isTile(j, i, Tile::WALL))
					std::cout << "¡á";
				else if (isTile(j, i, Tile::BROKEN_WALL))
					std::cout << "¡à";
				else if (isTile(j, i, Tile::ROAD))
					std::cout << "  ";
				else if (isTile(j, i, Tile::COIN))
					std::cout << "¡¤";
				else if (isTile(j, i, Tile::PLAYER_START))
					std::cout << "  ";
				else if (isTile(j, i, Tile::ENEMY_SPAWN))
					std::cout << "  ";
				else if (isTile(j, i, Tile::ITEM))
					std::cout << "¡Ú";
				
			}
			else
				std::cout << "  ";
		}
		std::cout << endl;
	}
}
