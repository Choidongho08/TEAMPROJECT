#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include "Map.h"

using namespace std;

// 8방향 이동을 위한 방향 배열 (순서 변경: 직선 이동을 먼저 검사)
const int dx[] = { 0, 0, -1, 1, -1, -1, 1, 1 };  // 상하좌우를 먼저, 그 다음 대각선
const int dy[] = { -1, 1, 0, 0, -1, 1, -1, 1 };

class AStar {
private:
    Map& map;
    double heuristic(int x1, int y1, int x2, int y2);
    vector<Node*> reconstructPath(Node* node);
public:
    AStar(Map& m) : map(m) {}
    vector<Node*> findPath(int startX, int startY, int goalX, int goalY, Map map);
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
