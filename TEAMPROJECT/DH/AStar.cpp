#include "AStar.h"

double AStar::heuristic(int x1, int y1, int x2, int y2) {
    // Manhattan distance와 Euclidean distance의 조합
    double deltaX = abs(x2 - x1);
    double deltaY = abs(y2 - y1);
    return 1.0 * (deltaX + deltaY) + (1.414 - 2.0) * min(deltaX, deltaY);
}
    
vector<Node*> AStar::reconstructPath(Node* node) {
    vector<Node*> path;
    while (node != nullptr) {
        path.push_back(node);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}


#include "../Core/Console.h"


vector<Node*> AStar::findPath(int startX, int startY, int goalX, int goalY) {
    // 1. 초기화
    // - 시작 노드를 열린 목록에 추가
    // - 시작 노드의 f, g 값 초기화
    Node* start = new Node(startX, startY);
    Node* goal = new Node(goalX, goalY);

    // priority_queue(우선순위 큐)는 내부적으로 힙(heap) 정렬을 사용하여 노드들을 f값에 따라 자동 정렬합니다.
    priority_queue<Node*, vector<Node*>, CompareNode> openPQ;           // 탐색할 노드들을 담는 목록
    vector<Node*> openList;                                             // 시각화를 위한 열린 목록
    vector<vector<bool>> closedList(map.ROW, vector<bool>(map.COL, false));     // 이미 탐색한 노드들을 담는 목록
    vector<vector<double>> gScore(map.ROW, vector<double>(map.COL, INFINITY));

    start->h = heuristic(startX, startY, goalX, goalY);                 // 시작 노드의 휴리스틱 비용
    start->f = start->h;                                                // f = g + h: 시작 노드의 총 예상 비용
    gScore[startY][startX] = 0;                                         // 시작 노드까지의 실제 비용

    openPQ.push(start);
    openList.push_back(start);

    vector<Node*> currentPath;
    int steps = 0;

    // 2. 반복 과정
    while (!openPQ.empty()) {
        // 2.1 현재 노드 선택
        // - 열린 목록에서 f값이 가장 작은 노드 선택
        Node* current = openPQ.top();
        openPQ.pop();

        // Open List에서 현재 노드 제거
        openList.erase(remove_if(openList.begin(), openList.end(),
            [current](Node* n) { return n->x == current->x && n->y == current->y; }),
            openList.end());

        steps++;

        // 3.2 목표 도달 확인
        // - 현재 노드가 목표 노드인지 확인
        if (current->x == goalX && current->y == goalY) {
            currentPath = reconstructPath(current);
             // cout << "\nPath found!\n";
            return currentPath;
        }

        // 2.3 노드 목록 업데이트
        // - 현재 노드를 닫힌 목록에 추가
        if (closedList[current->y][current->x]) {
            continue;
        }

        closedList[current->y][current->x] = true;
        currentPath = reconstructPath(current);

        // 2.4 인접 노드 탐색
        // - 현재 노드의 모든 인접 노드들을 평가
        for (int i = 0; i < 4; i++) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            // 이미 탐색한 노드는 건너뛰기
            if (!map.isWalkable(newX, newY) || closedList[newY][newX]) {
                continue;
            }

            // 2.5 비용 계산
            // - 시작 노드부터 인접 노드까지의 새로운 비용 계산
            double moveCost = 1.0;
            moveCost *= 0.9;

            double tentativeG = gScore[current->y][current->x] + moveCost;

            // 2.6 노드 추가 또는 업데이트
            // - 새로운 경로가 더 나은 경우 노드 정보 업데이트
            if (tentativeG < gScore[newY][newX]) {
                Node* neighbor = new Node(newX, newY);
                neighbor->parent = current;
                // # 2.7 비용 업데이트
                // # - 노드의 g값과 f값을 업데이트
                neighbor->g = tentativeG;
                neighbor->h = heuristic(newX, newY, goalX, goalY);
                neighbor->f = neighbor->g + neighbor->h;

                gScore[newY][newX] = tentativeG;
                openPQ.push(neighbor);
                openList.push_back(neighbor);
            }
        }
    }
    // 3. 종료 조건
    // - 목표에 도달할 수 없는 경우 (열린 목록이 비어있음)
    return vector<Node*>();
}

