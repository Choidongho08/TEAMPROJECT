#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <conio.h>
#include <windows.h>
using namespace std;

const int ROW = 20;
const int COL = 20;

// 노드 구조체
struct Node
{
    int x, y;  // 위치
    double g;  // 시작점으로부터의 비용
    double h;  // 휴리스틱 추정 비용
    double f;  // 총 비용 (f = g + h)
    Node* parent;  // 부모 노드

    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), f(0), parent(nullptr) {}
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        if (abs(a->f - b->f) < 0.0001) {  // f값이 같은 경우
            return a->h > b->h;  // h값이 작은 것을 우선
        }
        return a->f > b->f;
    }
};

// 8방향 이동을 위한 방향 배열 (순서 변경: 직선 이동을 먼저 검사)
const int dx[] = { 0, 0, -1, 1, -1, -1, 1, 1 };  // 상하좌우를 먼저, 그 다음 대각선
const int dy[] = { -1, 1, 0, 0, -1, 1, -1, 1 };

class Map {
private:
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

class AStar {
private:
    Map& map;
    double heuristic(int x1, int y1, int x2, int y2);
    vector<Node*> reconstructPath(Node* node);
public:
    AStar(Map& m) : map(m) {}
    vector<Node*> findPath(int startX, int startY, int goalX, int goalY);
};
/*
int main() {
    Map map;

    // 장애물 설정
    map.setObstacle(2, 2);
    map.setObstacle(2, 3);
    map.setObstacle(2, 4);
    map.setObstacle(3, 2);
    map.setObstacle(4, 2);

    cout << "Initial Map:" << endl;
    map.printMap();
    cout << "\nPress any key to start pathfinding...";
    _getch();

    AStar astar(map);
    vector<Node*> path = astar.findPath(0, 0, ROW - 1, COL - 1);

    if (!path.empty()) {
        cout << "\nFinal path found!\n";
        cout << "Path coordinates (x,y) and costs:\n";
        for (const auto& node : path) {
            cout << "Position: (" << node->x << "," << node->y << ") ";
            cout << "f=" << node->f << " g=" << node->g << " h=" << node->h << endl;
        }
        cout << "Total path length: " << path.size() << " nodes\n";
        cout << "Total path cost: " << path.back()->g << "\n";
        cout << "\nPress any key to exit...";
    }
    else {
        cout << "\nNo path found! Press any key to exit...";
    }

    _getch();
    return 0;
}
*/
