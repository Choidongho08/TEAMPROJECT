#include <math.h>
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
	_pos.tPos = startPos;
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
	for (int i = 1; i<=4; ++i)
	{
		Direction randDir = (Direction)i;
		Rotate(randDir);

		int x = _pos.tNewPos.x;
		int y = _pos.tNewPos.y;

		_pos.tNewPos.x = std::clamp(_pos.tNewPos.x, 0, _gameMap->GetMapCol());
		_pos.tNewPos.y = std::clamp(_pos.tNewPos.y, 0, _gameMap->GetMapRow());

		if (!_gameMap->isTile(x, y, Tile::WALL)) // ���� �ִ� ������ WALL�� �ƴϸ� ���ѷ��� �ƿ�
			break;
	}
	_forward = _pos.tNewPos - _pos.tPos;
	_pos.tPos = _pos.tNewPos;
}

void Enemy::AStarMove()
{
	// AStar�� �÷��̾ ���� ���� ������

}
