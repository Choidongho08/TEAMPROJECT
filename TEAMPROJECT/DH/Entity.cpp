#include "Entity.h"
#include "../Core/Console.h"

Entity::Entity(ENTITYPOS entityPos, EntityState entityState, ENTITY_TYPE _type, Map* _map)
	: pos(entityPos), state(entityState), dir(Direction::NONE), type(_type), map(_map)
{
}

void Entity::Rotate(Direction direction)
{
	switch (direction)
	{
	case Direction::RIGHT:
		pos.tForward = POS{ 0,1 };
		break;
	case Direction::LEFT:
		pos.tForward = POS{ 0, -1 };
		break;
	case Direction::UP:
		pos.tForward = POS{ -1, 0 };
		break;
	case Direction::DOWN:
		pos.tForward = POS{ 1, 0 };
		break;
	case Direction::NONE:
		pos.tForward = POS{ 0, 0 };
	}
}

void Entity::Rotate90()
{
	if (pos.tForward == POS{ 0, 0 })
	{
		pos.tForward == POS{ 0, 0 };
	}
	else if (pos.tForward == POS{ 1, 0 })
	{
		pos.tForward == POS{ 0, 1 };
	}
	else if (pos.tForward == POS{ 0, 1 })
	{
		pos.tForward == POS{ -1, 0 };
	}
	else if (pos.tForward == POS{ -1, 0 })
	{
		pos.tForward == POS{ 0, -1 };
	}
	else if (pos.tForward == POS{ 0, -1 })
	{
		pos.tForward == POS{ 1, 0 };
	}
}

void Entity::Rotate180()
{
	if (pos.tForward == POS{ 0, 0 })
	{
		pos.tForward == POS{ 0, 0 };
	}
	else if (pos.tForward == POS{ 1, 0 })
	{
		pos.tForward == POS{ -1, 0 };
	}
	else if (pos.tForward == POS{ 0, 1 })
	{
		pos.tForward == POS{ 0, -1 };
	}
	else if (pos.tForward == POS{ -1, 0 })
	{
		pos.tForward == POS{ 1, 0 };
	}
	else if (pos.tForward == POS{ 0, -1 })
	{
		pos.tForward == POS{ 0, 1 };
	}
}

void Entity::Render(std::string s)
{
	GotoXY(pos.tPos.x * 2, pos.tPos.y);
	cout << s;
}

void Entity::Move()
{
	if (!map->isTile(pos.tNewPos.x, pos.tNewPos.y, Tile::WALL))
	{
		pos.tPos = pos.tNewPos;
	}
	else
		pos.tNewPos = pos.tPos;
}
