#include "EnemyManager.h"
#include "PlayerManager.h"
#include "../Core/Console.h"

void PlayerManager::SpawnPlayer(vector<Entity*>& entities)
{
    ENTITYPOS pos;
    PlayerState state;
    pos = { 0 };
    pos.tStartPos = map->PlayerSpawnPos;
    pos.tPos = pos.tStartPos;
    state = { false, 0, 0, false, Skill::None, false, Skill::None };
    player = Player{ state, pos };
    player.Initialize(map->ROW, map->COL);
    entities.push_back(&player);
    return;
}

void PlayerManager::PlayerDead()
{
    player.state.isAlive = false;
}

void PlayerManager::SetSight(Map* _map)
{
}


