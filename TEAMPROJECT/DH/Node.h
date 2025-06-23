#pragma once
#include <cmath>
#include "Pos.h"
#include "Enums.h"

// ��� ����ü
struct Node
{
    int tile;
    POS pos;
    int x = pos.x;
    int y = pos.y;
    double g;  // ���������κ����� ���
    double h;  // �޸���ƽ ���� ���
    double f;  // �� ��� (f = g + h)
    Node* parent;  // �θ� ���

    Node(int _x, int _y) : tile((int)Tile::None), pos(POS{ _x, _y }), g(0), h(0), f(0), parent(nullptr) {}
    Node(int _tile, int _x, int _y) : tile(_tile), pos(POS{ _x, _y }), g(0), h(0), f(0), parent(nullptr) {}
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        if (abs(a->f - b->f) < 0.0001) {  // f���� ���� ���
            return a->h > b->h;  // h���� ���� ���� �켱
        }
        return a->f > b->f;
    }
};