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
    state = { true, 0, 0, false, SKILL::None, false, SKILL::None };
    Player newPlayer = Player{ state, pos, map };
    player = newPlayer;
    player.Initialize(map->ROW, map->COL);
    entities.push_back(&player);
    return;
}

void PlayerManager::PlayerDead()
{
    player.state.isAlive = false;
}



