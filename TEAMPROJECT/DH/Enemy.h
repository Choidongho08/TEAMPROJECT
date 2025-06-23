#pragma once
#include "Entity.h";
#include "AStar.h"

class EnemyState : public EntityState
{
public:
	bool isFollowing;
};

class Enemy : public Entity
{
public:
	EnemyState _state;
	AStar playerFindAStar;

private:

public:
	Enemy(AStar _aStar);

	void Initialize(
		POS _startPos,
		bool _isFollowing
	);

	void Move();
	void BasicMove();
	void AStarMove();

private:
};