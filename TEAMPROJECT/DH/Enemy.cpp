#include "Enemy.h"

Enemy::Enemy(Map& m) :
	_playerFindAStar(m),
	Entity({ {0,0}, {0,0}, {0,0} }, { true })
{
	_state = EnemyState{ true, false };
}

void Enemy::Initialize(POS startPos, bool isFollowing)
{
	_pos.tStartPos = startPos;
	_state = EnemyState{ true, isFollowing };
}

void Enemy::Move()
{
	if (_state.isFollowing)
	{
		AStarMove();
		return;
	}
	// 일반 움직임

}

void Enemy::AStarMove()
{
	// AStar로 플레이어를 향해 가는 움직임

}
