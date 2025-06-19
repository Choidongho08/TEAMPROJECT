#include "Map.h"

void Map::printMap(const vector<Node*>& path) {
	    vector<vector<char>> display(ROW, vector<char>(COL, '.'));
	
	    for (int i = 0; i < ROW; i++) {
	        for (int j = 0; j < COL; j++) {
	            if (grid[i][j] == 1) display[i][j] = '#';
	        }
	    }
	
	    for (auto node : path) {
	        display[node->x][node->y] = '*';
	    }
	
	    for (int i = 0; i < ROW; i++) {
	        for (int j = 0; j < COL; j++) {
	            cout << display[i][j] << ' ';
	        }
	        cout << endl;
	    }
	}
	
	void Map::printCurrentState(const vector<Node*>& path,
	    const vector<vector<bool>>& closedList,
	    const vector<Node*>& openList,
	    Node* current) {
	    vector<vector<char>> display(ROW, vector<char>(COL, '.'));
	
	    // 장애물 표시
	    for (int i = 0; i < ROW; i++) {
	        for (int j = 0; j < COL; j++) {
	            if (grid[i][j] == 1) display[i][j] = '#';
	        }
	    }
	
	    // Closed List 표시 (이미 검사한 노드)
	    for (int i = 0; i < ROW; i++) {
	        for (int j = 0; j < COL; j++) {
	            if (closedList[i][j]) display[i][j] = 'X';
	        }
	    }
	
	    // Open List 표시 (검사할 노드)
	    for (const auto& node : openList) {
	        display[node->x][node->y] = 'O';
	    }
	
	    // 현재 경로 표시
	    for (auto node : path) {
	        display[node->x][node->y] = '*';
	    }
	
	    // 현재 검사 중인 노드 표시
	    if (current) {
	        display[current->x][current->y] = 'C';
	    }
	
	    // 맵 상태 출력
	    system("cls");
	    cout << "\nCurrent Map State:\n";
	    cout << "C: Current Node, O: Open List, X: Closed List, *: Path, #: Obstacle\n\n";
	
	    for (int i = 0; i < ROW; i++) {
	        for (int j = 0; j < COL; j++) {
	            cout << display[i][j] << ' ';
	        }
	        cout << endl;
	    }
	
	    // Open List 정보 출력
	    cout << "\nOpen List Nodes:\n";
	    for (const auto& node : openList) {
	        cout << "(" << node->x << "," << node->y << ") ";
	        cout << "f=" << node->f << " g=" << node->g << " h=" << node->h << endl;
	    }
	
	    cout << "\nPass any key!" << endl;
	    _getch();
	}