#pragma once
#include <cmath>

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