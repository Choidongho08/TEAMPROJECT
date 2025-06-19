#pragma once
#include <cmath>

// ��� ����ü
struct Node
{
    int x, y;  // ��ġ
    double g;  // ���������κ����� ���
    double h;  // �޸���ƽ ���� ���
    double f;  // �� ��� (f = g + h)
    Node* parent;  // �θ� ���

    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), f(0), parent(nullptr) {}
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        if (abs(a->f - b->f) < 0.0001) {  // f���� ���� ���
            return a->h > b->h;  // h���� ���� ���� �켱
        }
        return a->f > b->f;
    }
};