#include "Enemy.h"

Enemy::Enemy() : Entity({ {0,0}, {0,0}, {0,0} }, { true })
{
	_state = EnemyState{ true, false };
}

void Enemy::Initialize(POS startPos, bool isFollowing)
{
	_pos.tStartPos = startPos;
	_state = EnemyState{ true, isFollowing };
}
