#include <math.h>
#include "../Core/Console.h"
#include "Enemy.h"

Enemy::Enemy(Map* _map) :
	id(0),
	Entity({ {0,0}, {0,0}, {0,0}, {0,1} },
	{ true },
	ENTITY_TYPE::Enemy,
	_map),
	playerFindAStar(*_map)
{
	PPlayer = nullptr;
	state = EnemyState{ true, false };
}

void Enemy::Initialize(EnemyState _state, POS _startPos, int _enemyCnt)
{
	state = _state;
	pos.tStartPos = _startPos;
	pos.tPos = _startPos;
	id = _enemyCnt;
}

void Enemy::Move()
{
	// if (_state.isFollowing)
	// {
// 		AStarMove(_map);
// 		return;
	// }
	POS newPos = pos.tPos + (pos.tForward == POS{ 0,0 } ? POS{ 1,0 } : pos.tForward); // ������ ������ �������� ���� ��
	if (!map->isTile(newPos.x, newPos.y, Tile::WALL) && newPos != pos.tPos)
	{
		pos.tNewPos = newPos;
		Entity::Move();
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		Entity::Move();
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		Entity::Move();
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		Entity::Move();
		return;
	}
	Entity::Move();
}

void Enemy::BasicMove()
{
}

void Enemy::Update()
{
}

void Enemy::AStarMove()
{
	// AStar�� �÷��̾ ���� ���� ������
	vector<Node*> path = playerFindAStar.findPath(pos.tPos.x, pos.tPos.y, PPlayer->pos.tPos.x, PPlayer->pos.tPos.y, *map);
	pos.tNewPos = path[0]->pos;
}
