#pragma once

typedef struct _pos
{
    int x;
    int y;

    bool operator == (const _pos& other) const
    {
        return (x == other.x && y == other.y);
    }
    _pos operator + (const _pos& other) const
    {
        return _pos(x + other.x, y + other.y);
    }
    _pos operator - (const _pos& other) const
    {
        return _pos(x - other.x, y - other.y);
    }
    _pos operator * (const int& num) const
    {
        return _pos(x * num, y * num);
    }
}POS, * PPOS;