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
	state = EnemyState{ true, false };
}

void Enemy::Initialize(EnemyState _state, POS _startPos, int _enemyCnt)
{
	state = _state;
	pos.tStartPos = _startPos;
	pos.tPos = _startPos;
	pos.tNewPos = _startPos;
	id = _enemyCnt;
}

void Enemy::EnemyMove()
{
	if (state.isFollowing)
	{
		AStarMove();
		return;
	}
}

void Enemy::Update()
{
	Move();
}

void Enemy::AStarMove()
{
	// AStar�� �÷��̾ ���� ���� ���
	vector<Node*> path = playerFindAStar.findPath(pos.tPos.x, pos.tPos.y, pPlayer->pos.tPos.x, pPlayer->pos.tPos.y);
	if (path.size() != 0)
	{
		// �÷��̾ ���� ���� ������
		if (!path.empty())
		{
			pos.tNewPos = path[1]->pos;
			pos.tForward = pos.tNewPos - pos.tPos;
		}
	}
	
}
