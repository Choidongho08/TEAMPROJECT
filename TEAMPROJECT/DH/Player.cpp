#include <thread>
#include <chrono>
#include "Player.h"
#include "../Core/Core.h"

Player::Player() : Entity(ENTITYPOS{{0,0}, {0,0}}, EntityState{false}, ENTITY_TYPE{ENTITY_TYPE::Player}, new Map())
{
}

Player::Player(PlayerState _state, ENTITYPOS _pos, Map* _map) : Entity(_pos, _state, ENTITY_TYPE::Player, _map)
{
    state = _state;
    pos = _pos;
    pos.tForward = { 0,0 };
    dashCnt = 1;
}

void Player::Initialize(
    int _mapHeight,
    int _mapWidth
)
{
    mapHeight = _mapHeight;
    mapWidth = _mapWidth;
    // state.maxSight = mapHeight * mapWidth / 10;
    state.maxSight = 100;
}

void Player::Update()
{
    if (state.isUsingSkill)
    {
        switch (state.usingSkill)
        {
        case Skill::DASH:
        {
            dashEndPos = (pos.tForward * dashCnt) + pos.tPos;
            if (map->isTile(dashEndPos.x, dashEndPos.y, Tile::WALL))
            {
                dashEndPos = dashEndPos - pos.tForward;
                state.isUsingSkill = false;
                dashCnt = 1;
            }
            pos.tNewPos = dashEndPos;
            dashCnt++;
            break;
        }
        case Skill::KILL:
        {
            state.isUsingSkill = false;
            break;
        }
        case Skill::SIGHT:
        {
            double curTime = clock() / CLOCKS_PER_SEC;
            if (skillMaxTime <= curTime - skillStartTime)
            {
                state.isUsingSkill = false;
                SetSight(max(3, 100 * (map->MapCoinCnt - state.score) / map->MapCoinCnt / 3));
            }
            break;
        }
        }

        skillStartTime = 0;
        skillMaxTime = 0;
    }
}

void Player::CheckTile()
{
    if (map->isTile(pos.tPos.x, pos.tPos.y, Tile::COIN))
    {
        state.score++;
        map->SetMapTile(pos.tPos.x, pos.tPos.y, Tile::ROAD);

        if (!(state.isUsingSkill && state.usingSkill == Skill::SIGHT))
            SetSight(max(2, 100 * (map->MapCoinCnt - state.score) / map->MapCoinCnt / 3));

        if (map->MapCoinCnt == state.score)
        {
            Core::Instance->ChangeScene(SCENE::WIN);
        }
    }
    if (map->isTile(pos.tPos.x, pos.tPos.y, Tile::ITEM))
    {
        if (state.isHaveSkill)
            return;

        state.isHaveSkill = true;
        srand((unsigned int)time(nullptr));
        int rVal = rand() % (int)Skill::END;
        state.haveSkill = (Skill)rVal;
        map->SetMapTile(pos.tPos.x, pos.tPos.y, Tile::ROAD);
    }
}

void Player::SetSight(int sight)
{
    GotoXY(0, 0);
    cout << "maxSight : " << sight;
    state.maxSight = sight;
}

void Player::SetSightTime(float time)
{
    skillMaxTime = time; // 왜인지 모르겠지만 1초 더 지나야 끝나서 1초 줄여줌
}

void Player::KillEnemy(const POS& killPos)
{
    if (OnKillEnemy)
        OnKillEnemy(killPos);
}

void Player::SetSkill(Skill skill)
{
    state.haveSkill = skill;
}

void Player::UseSkill()
{
    if (!state.isHaveSkill) return;
    else
    {
        skillStartTime = clock() / CLOCKS_PER_SEC;
        state.isHaveSkill = false;
        state.isUsingSkill = true;
        switch (state.haveSkill)
        {
        case Skill::KILL:
        {
            state.haveSkill = Skill::None;
            state.usingSkill = Skill::KILL;
            POS killPos = pos.tPos + pos.tForward;
            KillEnemy(killPos);
            break;
        }
        case Skill::SIGHT:
        {
            state.haveSkill = Skill::None;
            state.usingSkill = Skill::SIGHT;
            const int& sight = state.maxSight;
            SetSightTime(5);
            SetSight(sight * 2);
            break;
        }
        case Skill::DASH:
        {
            state.haveSkill = Skill::None;
            state.usingSkill = Skill::DASH;
            dashEndPos = POS{ 0,0 };
            int num = 1;
            break;
        }
        default:
            state.haveSkill = Skill::None;
            state.isUsingSkill = false;
            false;
        }
    }
}
