#include "Map.h"
#include "../Core/Console.h"
#include <cmath>
#include <fstream>

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
			}
			if (col.tile == (int)Tile::COIN)
				MapCoinCnt++;
		}
	}

	MaxPlayerFollowingEnemyCnt = EnemySpawnPos.size();
}

void Map::ItemInit()
{
	int itemCount = 0;
	srand((unsigned int)time(NULL));
	MaxItemCnt = Random(6, 5);
	while (itemCount < MaxItemCnt)
	{
		int y = rand() % ROW;
		int x = rand() % COL;

		if (isTile(x, y, Tile::COIN))
		{
			SetMapTile(x, y, Tile::ITEM);
			itemCount++;
			MapCoinCnt--;
		}
	}
}

void Map::LoadStage()
{
	srand((unsigned int)time(NULL));
	int stageNumber = rand() % 3 + 1;
	string mapFileName = "Stage" + std::to_string(stageNumber) + ".txt";
	Stage = stageNumber;
	std::ifstream mapFile(mapFileName);
	if (mapFile.is_open())
	{
		// �ʱ�ȭ
		std::string line;

		int x = 0;
		int y = 0;

		std::vector<std::vector<Node>> grid;

		while (std::getline(mapFile, line))
		{
			x = 0;
			std::vector<Node> rowGrid;
			for (char ch : line)
			{
				Node col = Node(ch - '0', x, y);
				rowGrid.push_back(col);
				x++;
			}
			grid.push_back(rowGrid);
			y++;
		} // �� ���� ���ϸ鼭 �� �ʱ�ȭ

		InitializeMap(grid);
		SetMapRowCol(y, x);
		mapFile.close();
		return;
	}
	else
		cout << "�� ���� �ʱ�ȭ ����" << endl;
}

void Map::Render(const int& x, const int& y, const int& distance)
{
	COORD resolution = GetConsoleResolution(); // �ܼ� ũ�� ��������
	int offsetX = (resolution.X - COL * 2) / 2; // ���� �ʺ� 2ĭ
	int offsetY = 2;

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			int dx = j - x;
			int dy = i - y;
			GotoXY(offsetX + j * 2, offsetY + i); // �� �߾� ���� ��ġ�� ���
			if (dx * dx + dy * dy <= distance * distance)
			{
				if (isTile(j, i, Tile::WALL))
					std::cout << "��";
				else if (isTile(j, i, Tile::BROKEN_WALL))
					std::cout << "��";
				else if (isTile(j, i, Tile::ROAD))
					std::cout << "  ";
				else if (isTile(j, i, Tile::COIN))
					std::cout << "��";
				else if (isTile(j, i, Tile::PLAYER_START))
					std::cout << "  ";
				else if (isTile(j, i, Tile::ENEMY_SPAWN))
					std::cout << "  ";
				else if (isTile(j, i, Tile::ITEM))
					std::cout << "��";
				else if(isTile(j, i, Tile::BEDROCK))
					std::cout << "��";
				else
					std::cout <<  "  ";
			}
			else
				std::cout << "  ";
		}
	}
}

