#pragma once
#include "Player.h"
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
	Player* PPlayer;
	AStar playerFindAStar;

private:

public:
	Enemy(AStar _aStar);

	void Initialize(
		POS _startPos,
		bool _isFollowing
	);

	void Move(Map* _map);
	void BasicMove();
	void AStarMove(Map* _map);

private:
};