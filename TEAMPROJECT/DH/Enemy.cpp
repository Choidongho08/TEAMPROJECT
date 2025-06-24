#include <math.h>
#include "../Core/Console.h"
#include "Enemy.h"

Enemy::Enemy(AStar _aStar) :
	Entity({ {0,0}, {0,0}, {0,0} },
	{ true },
	ENTITY_TYPE::Enemy),
	playerFindAStar(_aStar)
{
	PPlayer = nullptr;
	_state = EnemyState{ true, false };
}

void Enemy::Initialize(POS _startPos, bool _isFollowing)
{
	pos.tStartPos = _startPos;
	pos.tPos = _startPos;
	_state = EnemyState{ true, _isFollowing };
}

void Enemy::Move(Map* _map)
{
	if (_state.isFollowing)
	{
		AStarMove(_map);
		return;
	}
	POS newPos = pos.tPos + pos.tForward; // ������ ������ �������� ���� ��
	if (!_map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!_map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!_map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!_map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		return;
	}
}

void Enemy::BasicMove()
{
}

void Enemy::AStarMove(Map* _map)
{
	// AStar�� �÷��̾ ���� ���� ������
	vector<Node*> path = playerFindAStar.findPath(pos.tPos.x, pos.tPos.y, PPlayer->pos.tPos.x, PPlayer->pos.tPos.y, *_map);
	pos.tNewPos = path[0]->pos;
}
