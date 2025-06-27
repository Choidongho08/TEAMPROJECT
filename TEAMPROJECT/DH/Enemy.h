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
	EnemyState state;
	Player* PPlayer;
	AStar playerFindAStar;

private:
	int id;

public:
	Enemy(AStar _aStar);

	bool operator==(const Enemy& other) const {
		return this->id == other.id;
	}

	void Initialize(
		EnemyState _state,
		POS _startPos,
		int _enemyCnt
	);

	void Move(Map* _map);
	void BasicMove();
	void Update();
	void AStarMove(Map* _map);

private:
};