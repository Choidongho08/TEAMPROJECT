#include "Entity.h"
#include "../Core/Console.h"

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
		_pos.tNewPos = POS{ 0,1 } + _pos.tPos;
		break;
	case Direction::LEFT:
		_pos.tNewPos = POS{ 0, -1 } + _pos.tPos;
		break;
	case Direction::UP:
		_pos.tNewPos = POS{ -1, 0 } + _pos.tPos;
		break;
	case Direction::DOWN:
		_pos.tNewPos = POS{ 1, 0 } + _pos.tPos;
		break;
	}
}

void Entity::Render(std::string s)
{
	COUT(s);
}
