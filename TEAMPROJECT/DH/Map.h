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
    int Stage = 0;

private:
    vector<vector<Node>> grid;

public:
    Map() : MapCoinCnt(0), MaxItemCnt(0), grid(0), ROW(0), COL(0), PlayerSpawnPos(POS{0,0}), EnemySpawnPos(0), MaxPlayerFollowingEnemyCnt(0)
    {}

    void InitializeMap(const vector<vector<Node>>& _grid);

    void ItemInit();

    void LoadStage();

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

    void Render(const int& x, const int& y, const int& distance);

    void setObstacle(int x, int y)
    {
        if (isValid(x, y)) grid[y][x].tile = (int)Tile::WALL;
    }

    bool isTile(int x, int y, Tile tile)
    {
        return grid[y][x].tile == (int)tile;
    }

    bool isValid(int x, int y) const
    {
        return x >= 0 && x < COL && y >= 0 && y < ROW;
    }

    bool isWalkable(int x, int y) const 
    {
        return isValid(x, y) && grid[y][x].tile != (int)Tile::WALL && grid[y][x].tile != (int)Tile::BEDROCK;
    }
};

