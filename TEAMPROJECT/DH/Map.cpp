#include "Map.h"
#include "Debug.h"

void Map::InitializeMap(const vector<vector<Node>>& _grid)
{
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
	Debug::Instance->Pos(__FUNCTION__, __LINE__);
	Debug::Instance->Log(PlayerSpawnPos.x);
	Debug::Instance->Log(PlayerSpawnPos.y);
}

void Map::Render(int x, int y)
{
	// 타일 그리기
	if (isTile(x, y, Tile::WALL))
		std::cout << "■";
	else if (isTile(x, y, Tile::BROKEN_WALL))
		std::cout << "□";
	else if (isTile(x, y, Tile::ROAD))
		std::cout << "  ";
	else if (isTile(x, y, Tile::COIN))
		std::cout << "·";
	else if (isTile(x, y, Tile::PLAYER_START))
		std::cout << "  ";
	else if (isTile(x, y, Tile::ENEMY_SPAWN))
		std::cout << "  ";
	else if (isTile(x, y, Tile::ITEM))
		std::cout << "★";
}
