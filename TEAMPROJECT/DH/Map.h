#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include "Enums.h"
#include "Pos.h"

using std::vector;

class Map {
public:
    vector<POS> EnemySpawnPos;
    POS PlayerSpawnPos;
    int MapCoinCnt;
    int MaxPlayerFollowingEnemyCnt;
    int MaxItemCnt;
    int ROW;
    int COL;

private:
    vector<vector<Node>> grid;

public:
    Map() : MapCoinCnt(0), MaxItemCnt(0), grid(0), ROW(0), COL(0), PlayerSpawnPos(POS{0,0}), EnemySpawnPos(0), MaxPlayerFollowingEnemyCnt(0)
    {}

    void InitializeMap(const vector<vector<Node>>& _grid);

    void SetMapTile(int _x, int _y, Tile _tile)
    {
        grid[_y][_x].tile = (int)_tile;
    }

    void SetMapRowCol(int _row, int _col)
    {
        ROW = _row;
        COL = _col;
    }

    const vector<vector<Node>> GetGrid()
    {
        return grid;
    }

    void Render(int x, int y);

    void setObstacle(int x, int y)
    {
        if (isValid(x, y)) grid[x][y].tile = (int)Tile::WALL;
    }

    bool isTile(int x, int y, Tile tile)
    {
        return grid[y][x].tile == (int)tile;
    }

    bool isValid(int x, int y) const
    {
        return x >= 0 && x < ROW && y >= 0 && y < COL;
    }

    bool isWalkable(int x, int y) const 
    {
        return isValid(x, y) && grid[y][x].tile != (int)Tile::WALL;
    }

    bool isDiagonalWalkable(int x1, int y1, int x2, int y2) const 
    {
        return isWalkable(x1, y2) && isWalkable(x2, y1);
    }
};

