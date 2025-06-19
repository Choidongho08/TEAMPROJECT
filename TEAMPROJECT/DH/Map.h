#pragma once
#include <vector>
#include "Node.h"

using std::vector;

class Map {
private:
    int ROW;
    int COL;
    vector<vector<int>> grid;

public:
    Map() : grid(ROW, vector<int>(COL, 0)) {}

    void setObstacle(int x, int y) {
        if (isValid(x, y)) grid[x][y] = 1;
    }

    bool isValid(int x, int y) const {
        return x >= 0 && x < ROW && y >= 0 && y < COL;
    }

    bool isWalkable(int x, int y) const {
        return isValid(x, y) && grid[x][y] == 0;
    }

    bool isDiagonalWalkable(int x1, int y1, int x2, int y2) const {
        return isWalkable(x1, y2) && isWalkable(x2, y1);
    }

    void printCurrentState(const vector<Node*>& path,
        const vector<vector<bool>>& closedList,
        const vector<Node*>& openList,
        Node* current = nullptr);

    void printMap(const vector<Node*>& path = vector<Node*>());
};

