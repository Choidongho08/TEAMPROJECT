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
	Player* pPlayer;
	AStar playerFindAStar;
	int aStarDuration= 0;

private:
	int id;
	int aStarSpeed = 0;

public:
	Enemy(Map* _map);

	bool operator==(const Enemy& other) const {
		return this->id == other.id;
	}

	void Initialize(
		EnemyState _state,
		POS _startPos,
		int _enemyCnt
	);

	void EnemyMove();
	void Update();
	void AStarMove();

private:
};