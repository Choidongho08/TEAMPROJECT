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
    state.curSight = 100;
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

                skillStartTime = 0;
                skillMaxTime = 0;
                state.usingSkill = Skill::None;
            }
            pos.tNewPos = dashEndPos;
            dashCnt++;
            break;
        }
        case Skill::KILL:
        {
            state.isUsingSkill = false;
            skillStartTime = 0;
            skillMaxTime = 0;
            state.usingSkill = Skill::None;
            break;
        }
        case Skill::SIGHT:
        {
            double curTime = clock() / CLOCKS_PER_SEC;
            if (skillMaxTime <= curTime - skillStartTime)
            {
                state.isUsingSkill = false;
                SetSight(max(3, 100 * (map->MapCoinCnt - state.score) / map->MapCoinCnt / 3));
                skillStartTime = 0;
                skillMaxTime = 0;
                state.usingSkill = Skill::None;
            }
            break;
        }
        }
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

        srand((unsigned int)time(nullptr));
        int rVal = rand() % (int)Skill::END;
        SetSkill((Skill)rVal);
        map->SetMapTile(pos.tPos.x, pos.tPos.y, Tile::ROAD);
    }
}

void Player::SetSight(int sight)
{
    state.curSight = sight;
}

void Player::SetSkillTime(float time)
{
    skillMaxTime = time;
}

void Player::KillEnemy(const POS& killPos)
{
    if (OnKillEnemy)
        OnKillEnemy(killPos);
}

void Player::SetSkill(Skill skill)
{
    state.isHaveSkill = true;
    state.haveSkill = skill;
}

void Player::UseSkill()
{
    if (!state.isHaveSkill) return;
    else
    {
        skillStartTime = clock() / CLOCKS_PER_SEC;
        GotoXY(0, 0);
        cout << "UseSkill";
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
            const int& sight = state.curSight;
            SetSkillTime(3);
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
