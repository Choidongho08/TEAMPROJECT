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
	pPlayer = nullptr;
	pAStarPath = nullptr;
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
	if (state.isFollowing)
	{
		AStarMove();
		return;
	}
	// POS newPos = pos.tPos + (pos.tForward == POS{ 0,0 } ? POS{ 1,0 } : pos.tForward); // 기존에 움직인 방향으로 갔을 때
	// if (!map->isTile(newPos.x, newPos.y, Tile::WALL) && newPos != pos.tPos)
	// {
	// 	pos.tNewPos = newPos;
	// 	return;
	// }
	// Rotate90();
	// newPos = pos.tPos + pos.tForward;
	// if (!map->isTile(newPos.x, newPos.y, Tile::WALL))
	// {
	// 	pos.tNewPos = newPos;
	// 	return;
	// }
	// Rotate90();
	// newPos = pos.tPos + pos.tForward;
	// if (!map->isTile(newPos.x, newPos.y, Tile::WALL))
	// {
	// 	pos.tNewPos = newPos;
	// 	return;
	// }
	// Rotate90();
	// newPos = pos.tPos + pos.tForward;
	// if (!map->isTile(newPos.x, newPos.y, Tile::WALL))
	// {
	// 	pos.tNewPos = newPos;
	// 	return;
	// }
}

void Enemy::BasicMove()
{
}

void Enemy::Update()
{
	Entity::Move();
}

void Enemy::SettingAStar()
{
	// AStar로 플레이어를 향해 가는 경로
	vector<Node*> path = playerFindAStar.findPath(pos.tPos.x, pos.tPos.y, pPlayer->pos.tPos.x, pPlayer->pos.tPos.y);
	if (path.size() != 0)
	{
		aStarPath = path;
		pAStarPath = &aStarPath;
	}
}

void Enemy::AStarMove()
{
	// 플레이어를 향해 가는 움직임
	if (pAStarPath != nullptr)
	{
		pos.tNewPos = (*pAStarPath)[1]->pos;
		pos.tForward = pos.tNewPos - pos.tPos;
	}
}
