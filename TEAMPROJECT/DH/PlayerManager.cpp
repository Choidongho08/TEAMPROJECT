#include "EnemyManager.h"
#include "PlayerManager.h"
#include "../Core/Console.h"
#include "Debug.h"

void PlayerManager::SpawnPlayer(vector<Entity*>& entities)
{
    ENTITYPOS pos;
    PlayerState state;
    pos = { 0 };
    pos.tStartPos = map->PlayerSpawnPos;
    pos.tPos = pos.tStartPos;
    state = { 0, false, (int)Skill::None };
    player = Player{ state, pos };
    player.Initialize(map->ROW, map->COL);
    entities.push_back(&player);
    Debug::Instance->Pos(__FUNCTION__, __LINE__);
    Debug::Instance->Log(to_string(map->PlayerSpawnPos.x) + ", " + to_string(map->PlayerSpawnPos.y));
    return;
}

void PlayerManager::PlayerDead()
{
    player.state.isAlive = false;
}

void PlayerManager::SetSight(Map* _map)
{
    player.SetSight(max(3, 100 * (_map->MapCoinCnt - player.state.score) / _map->MapCoinCnt / 2));
    Debug::Instance->Log(to_string(100 * (_map->MapCoinCnt - player.state.score) / _map->MapCoinCnt));
}


