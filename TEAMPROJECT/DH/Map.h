#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include "Enums.h"

using std::vector;

class Map {
private:
    int ROW;
    int COL;
    vector<vector<int>> grid;

public:
    Map() : ROW(0), COL(0) {}

    void InitializeMap(vector<int> tile)
    {
        grid.push_back(tile);
    }

    void SetMapTile(int x, int y, Tile tile)
    {
        grid[x][y] = (int)tile;
    }

    void SetMapRowCol(int row, int col)
    {
        ROW = row;
        COL = col;
    }

    int GetMapRow()
    {
        return ROW;
    }
    int GetMapCol()
    {
        return COL;
    }

    void setObstacle(int x, int y) 
    {
        if (isValid(x, y)) grid[x][y] = 1;
    }

    bool isTile(int x, int y, Tile tile)
    {
        return grid[x][y] == (int)tile;
    }

    bool isValid(int x, int y) const
    {
        return x >= 0 && x < ROW && y >= 0 && y < COL;
    }

    bool isWalkable(int x, int y) const 
    {
        return isValid(x, y) && grid[x][y] == 0;
    }

    bool isDiagonalWalkable(int x1, int y1, int x2, int y2) const 
    {
        return isWalkable(x1, y2) && isWalkable(x2, y1);
    }
};

