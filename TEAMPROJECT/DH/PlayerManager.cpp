#include "EnemyManager.h"
#include "PlayerManager.h"
#include "../Core/Console.h"
#include "Debug.h"

void PlayerManager::SpawnPlayer(vector<Entity>& entities)
{
    ENTITYPOS pos;
    PlayerState state;
    pos = { 0 };
    pos.tStartPos = map->PlayerSpawnPos;
    pos.tPos = pos.tStartPos;
    state = { 0, false, (int)Skill::None };
    player = Player{ state, pos };
    entities.push_back(player);
    Debug::Instance->Pos(__FILE__, __LINE__);
    Debug::Instance->Log(to_string(map->PlayerSpawnPos.x) + ", " + to_string(map->PlayerSpawnPos.y));
    return;
}
