#include "../Core/Console.h"
#include "Enemy.h"

Enemy::Enemy(Map& m) :
	_playerFindAStar(m),
	Entity({ {0,0}, {0,0}, {0,0} }, { true })
{
	_state = EnemyState{ true, false };
	_gameMap = &m;
}

void Enemy::Initialize(POS startPos, bool isFollowing)
{
	_pos.tStartPos = startPos;
	_state = EnemyState{ true, isFollowing };
}

void Enemy::Move()
{
	for (;;)
	{
		int randValue = Random(4, 1);
		Direction randDir = (Direction)randValue;
		Rotate(randDir);

		int x = (_pos.tPos + _forward).x;
		int y = (_pos.tPos + _forward).y;
		if (!_gameMap->isTile(x, y, Tile::WALL)) // 보고 있는 방향이 WALL이 아니면 무한루프 아웃
			break;
	}
	if (_state.isFollowing)
	{
		AStarMove();
		return;
	}
	// 일반 움직임
	_pos.tNewPos = _pos.tPos + _forward;
}

void Enemy::AStarMove()
{
	// AStar로 플레이어를 향해 가는 움직임

}
