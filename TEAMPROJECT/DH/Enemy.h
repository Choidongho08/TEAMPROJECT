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
	int id;

public:
	Enemy(AStar _aStar);

	bool operator==(const Enemy& other) const {
		return this->id == other.id;
	}

	void Initialize(
		POS _startPos,
		bool _isFollowing,
		int _enemyCnt
	);

	void Move(Map* _map);
	void BasicMove();
	void AStarMove(Map* _map);

private:
};