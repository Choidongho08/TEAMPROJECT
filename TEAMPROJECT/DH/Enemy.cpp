#include <math.h>
#include "../Core/Console.h"
#include "Enemy.h"

Enemy::Enemy(AStar _aStar) :
	Entity({ {0,0}, {0,0}, {0,0} },
	{ true },
	ENTITY_TYPE::Enemy),
	playerFindAStar(_aStar)
{
	_state = EnemyState{ true, false };
}

void Enemy::Initialize(POS _startPos, bool _isFollowing)
{
	pos.tStartPos = _startPos;
	pos.tPos = _startPos;
	_state = EnemyState{ true, _isFollowing };
}

void Enemy::Move()
{
	if (_state.isFollowing)
	{
		AStarMove();
		return;
	}
	// if()
}

void Enemy::BasicMove()
{
	int x = pos.tNewPos.x;
	int y = pos.tNewPos.y;
}

void Enemy::AStarMove()
{
	// AStar로 플레이어를 향해 가는 움직임

}
