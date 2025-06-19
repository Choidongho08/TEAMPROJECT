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
	// �Ϲ� ������

}

void Enemy::AStarMove()
{
	// AStar�� �÷��̾ ���� ���� ������

}
