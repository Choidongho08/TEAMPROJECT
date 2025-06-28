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

private:
	int id;
	vector<Node*> aStarPath;
	vector<Node*>* pAStarPath;

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

	void Move();
	void BasicMove();
	void Update();
	void SettingAStar();
	void AStarMove();

private:
};