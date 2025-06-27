#include "Map.h"
#include "../Core/Console.h"
#include <cmath>

void Map::InitializeMap(const vector<vector<Node>>& _grid)
{
	MaxItemCnt = Random(5, 5);
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
			if (col.tile == (int)Tile::COIN)
				MapCoinCnt++;
		}
	}
}

void Map::Render(const int& x, const int& y, const int& distance)
{
	COORD resolution = GetConsoleResolution(); // 콘솔 크기 가져오기
	int offsetX = (resolution.X - COL * 2) / 2; // 문자 너비 2칸
	int offsetY = 0;

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			int dx = j - x;
			int dy = i - y;
			if (dx * dx + dy * dy <= distance * distance)
			{
				GotoXY(offsetX + j * 2, offsetY + i); // ← 중앙 정렬 위치로 출력
				if (isTile(j, i, Tile::WALL))
					std::cout << "■";
				else if (isTile(j, i, Tile::BROKEN_WALL))
					std::cout << "□";
				else if (isTile(j, i, Tile::ROAD))
					std::cout << "  ";
				else if (isTile(j, i, Tile::COIN))
					std::cout << "·";
				else if (isTile(j, i, Tile::PLAYER_START))
					std::cout << "  ";
				else if (isTile(j, i, Tile::ENEMY_SPAWN))
					std::cout << "  ";
				else if (isTile(j, i, Tile::ITEM))
					std::cout << "★";
				else if (isTile(j, i, Tile::PLAYER_START))
					continue; // 플레이어 위치 생략
				else if (isTile(j, i, Tile::ENEMY_SPAWN))
					continue; // 적 위치 생략
			}
			else
				std::cout << "  ";
		}
	}
}

