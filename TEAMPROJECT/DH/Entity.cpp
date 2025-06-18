#include "Entity.h"

Entity::Entity(ENTITYPOS entityPos, EntityState entityState)
	: _pos(entityPos), _state(entityState)
{
}

Entity::~Entity()
{
}
