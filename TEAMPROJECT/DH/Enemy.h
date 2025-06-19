#pragma once
#include "Entity.h";

class EnemyState : public EntityState
{
public:
	bool isFollowing;
};

class Enemy : public Entity
{
public:
	EnemyState _state;
private:

public:
	Enemy()
	void Initialize(
		POS startPos,
		bool isFollowing
	);
private:
};