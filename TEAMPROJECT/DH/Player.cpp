#include <thread>
#include <chrono>
#include "Player.h"
#include "../Core/Core.h"

Player::Player() : Entity(ENTITYPOS{{0,0}, {0,0}}, EntityState{false}, ENTITY_TYPE{ENTITY_TYPE::Player}, new Map())
{
    Clear = false;
}

Player::Player(PlayerState _state, ENTITYPOS _pos, Map* _map) : Entity(_pos, _state, ENTITY_TYPE::Player, _map)
{
    state = _state;
    pos = _pos;
    pos.tForward = { 0,0 };
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
        case SKILL::DASH:
        {
            while (true)
            {
                dashEndPos = pos.tForward + pos.tPos;
                if (map->isTile(dashEndPos.x, dashEndPos.y, Tile::WALL))
                {
                    dashEndPos = dashEndPos - pos.tForward;
                    state.isUsingSkill = false;

                    skillStartTime = 0;
                    skillMaxTime = 0;
                    state.usingSkill = SKILL::None;
                    break;
                }
                pos.tNewPos = dashEndPos;
                pos.tPos = pos.tNewPos;
                CheckTile();
            }
            break;
        }
        case SKILL::KILL:
        {
            KillEnemy(pos.tForward + pos.tPos);
            state.isUsingSkill = false;
            skillStartTime = 0;
            skillMaxTime = 0;
            state.usingSkill = SKILL::None;
            break;
        }
        case SKILL::SIGHT:
        {
            double curTime = clock() / CLOCKS_PER_SEC;
            if (skillMaxTime <= curTime - skillStartTime)
            {
                state.isUsingSkill = false;
                SetSight(max(3, 100 * (map->MapCoinCnt - state.score) / map->MapCoinCnt / 4));
                skillStartTime = 0;
                skillMaxTime = 0;
                state.usingSkill = SKILL::None;
            }
            break;
        }
        }
    }
    Move();
    CheckTile();
}

void Player::CrossAnimation()
{
    StopSound(SOUNDID::GAME);
    COORD resolution = GetConsoleResolution();
    int delaytime = 20;
    SetColor(COLOR::BLACK, COLOR::WHITE);
    for (int i = 0; i < resolution.X / 2; ++i)
    {
        for (int j = 0; j < resolution.Y; j += 2)
        {
            GotoXY(i * 2, j);
            cout << "  ";
        }
        for (int j = 1; j < resolution.Y; j += 2)
        {
            GotoXY(resolution.X - 2 - i * 2, j);
            cout << "  ";
        }
        Sleep(delaytime);
    }
    SetColor();
    Core::Instance->ChangeScene(SCENE::WIN);
}

void Player::CheckTile()
{
    if (map->isTile(pos.tPos.x, pos.tPos.y, Tile::COIN))
    {
        PlaySoundID(SOUNDID::COIN);
        state.score++;
        map->SetMapTile(pos.tPos.x, pos.tPos.y, Tile::ROAD);

        if (!(state.isUsingSkill && state.usingSkill == SKILL::SIGHT))
            SetSight(max(2, 100 * (map->MapCoinCnt - state.score) / map->MapCoinCnt / 4));

        if (map->MapCoinCnt == state.score)
        {
            Clear = true;
            CrossAnimation();
            return;
        }
    }
    if (map->isTile(pos.tPos.x, pos.tPos.y, Tile::ITEM))
    {
        if (state.isHaveSkill)
            return;

        srand((unsigned int)time(nullptr));
        int rVal = rand() % (int)SKILL::END;
        SetSkill((SKILL)rVal);
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

void Player::SetSkill(SKILL skill)
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
        case SKILL::KILL:
        {
            state.haveSkill = SKILL::None;
            state.usingSkill = SKILL::KILL;
            POS killPos = pos.tPos + pos.tForward;
            KillEnemy(killPos);
			PlaySoundID(SOUNDID::KILL);
            break;
        }
        case SKILL::SIGHT:
        {
            state.haveSkill = SKILL::None;
            state.usingSkill = SKILL::SIGHT;
            const int& sight = state.curSight;
            SetSkillTime(3);
            SetSight(sight * 2);
            PlaySoundID(SOUNDID::SIGHT);
            break;
        }
        case SKILL::DASH:
        {
            state.haveSkill = SKILL::None;
            state.usingSkill = SKILL::DASH;
            dashEndPos = POS{ 0,0 };
            int num = 1;
            PlaySoundID(SOUNDID::DASH);
            break;
        }
        default:
            state.haveSkill = SKILL::None;
            state.isUsingSkill = false;
            false;
        }
    }
}
