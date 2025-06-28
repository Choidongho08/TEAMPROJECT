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
	aStarSpeed++;
	if (aStarSpeed >= aStarDuration)
	{
		// AStar로 플레이어를 향해 가는 경로
		vector<Node*> path = playerFindAStar.findPath(pos.tPos.x, pos.tPos.y, pPlayer->pos.tPos.x, pPlayer->pos.tPos.y);
		if (path.size() != 0)
		{
			// 플레이어를 향해 가는 움직임
			if (!path.empty())
			{
				if (path.size() > 1)
					pos.tNewPos = path[1]->pos;
				else if (path.size() == 1)
					pos.tNewPos = path[0]->pos;
				pos.tForward = pos.tNewPos - pos.tPos;
			}
		}
		aStarSpeed = 0;
	}
}
