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
	AStar _playerFindAStar;

private:
	Map* _gameMap;

public:
	Enemy(Map& m);

	void Initialize (
		POS startPos,
		bool isFollowing
	);
	void Move();
	void AStarMove();
private:
};