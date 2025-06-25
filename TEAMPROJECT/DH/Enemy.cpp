#include <math.h>
#include "../Core/Console.h"
#include "Enemy.h"

Enemy::Enemy(AStar _aStar) :
	id(0),
	Entity({ {0,0}, {0,0}, {0,0}, {0,1} },
	{ true },
	ENTITY_TYPE::Enemy),
	playerFindAStar(_aStar)
{
	PPlayer = nullptr;
	_state = EnemyState{ true, false };
}

void Enemy::Initialize(POS _startPos, bool _isFollowing, int _enemyCnt)
{
	pos.tStartPos = _startPos;
	pos.tPos = _startPos;
	id = _enemyCnt;
	_state = EnemyState{ true, _isFollowing };
}

void Enemy::Move(Map* _map)
{
	// if (_state.isFollowing)
	// {
// 		AStarMove(_map);
// 		return;
	// }
	POS newPos = pos.tPos + pos.tForward; // 기존에 움직인 방향으로 갔을 때
	if (!_map->isTile(newPos.x, newPos.y, Tile::WALL) && newPos != pos.tPos)
	{
		pos.tNewPos = newPos;
		Entity::Move(_map);
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!_map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		Entity::Move(_map);
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!_map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		Entity::Move(_map);
		return;
	}
	Rotate90();
	newPos = pos.tPos + pos.tForward;
	if (!_map->isTile(newPos.x, newPos.y, Tile::WALL))
	{
		pos.tNewPos = newPos;
		Entity::Move(_map);
		return;
	}
	Entity::Move(_map);
}

void Enemy::BasicMove()
{
}

void Enemy::AStarMove(Map* _map)
{
	// AStar로 플레이어를 향해 가는 움직임
	vector<Node*> path = playerFindAStar.findPath(pos.tPos.x, pos.tPos.y, PPlayer->pos.tPos.x, PPlayer->pos.tPos.y, *_map);
	pos.tNewPos = path[0]->pos;
}
