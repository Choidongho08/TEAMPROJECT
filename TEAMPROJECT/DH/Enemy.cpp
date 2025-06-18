#include "Enemy.h"

Enemy::Enemy() : Entity({ {0,0}, {0,0}, {0,0} }, { true })
{
	_state = { false };
}
