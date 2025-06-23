#include "EnemyManager.h"
#include "PlayerManager.h"
#include "../Core/Console.h"

void PlayerManager::SpawnPlayer(vector<Entity>& entities)
{
    for (int i = 0; i < map.ROW; ++i)
    {
        for (int j = 0; j < map.COL; ++j)
        {
            if (map.isTile(j, i, Tile::PLAYER_START))
            {
                ENTITYPOS pos;
                PlayerState state;
                pos = { 0 };
                pos.tStartPos = POS{ j, i };
                pos.tPos = POS{ j, i };
                state = { 0, false, (int)Skill::None };
                player = Player{ state, pos };
                return;
            }
        }
    }
}
