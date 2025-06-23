#include "EnemyManager.h"
#include "PlayerManager.h"
#include "../Core/Console.h"
#include "Debug.h"

void PlayerManager::SpawnPlayer(vector<Entity>& entities)
{
    ENTITYPOS pos;
    PlayerState state;
    pos = { 0 };
    pos.tStartPos = map.PlayerSpawnPos;
    pos.tPos = pos.tStartPos;
    state = { 0, false, (int)Skill::None };
    player = Player{ state, pos };
    Debug::Instance->Log(to_string(pos.tStartPos.x) + ", " + to_string(pos.tStartPos.y));
    return;
}
