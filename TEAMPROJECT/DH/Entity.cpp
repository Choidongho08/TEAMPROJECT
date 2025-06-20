#include "Entity.h"

Entity::Entity(ENTITYPOS entityPos, EntityState entityState)
	: _pos(entityPos), _state(entityState), _forward(POS{-1,0})
{
}

Entity::~Entity()
{
}

void Entity::Rotate(Direction direction)
{
	switch (direction)
	{
	case Direction::RIGHT:
		_forward = POS{ 0,1 };
		break;
	case Direction::LEFT:
		_forward = POS{ 0, -1 };
		break;
	case Direction::UP:
		_forward = POS{ -1, 0 };
		break;
	case Direction::DOWN:
		_forward = POS{ 1, 0 };
		break;
	}
}
