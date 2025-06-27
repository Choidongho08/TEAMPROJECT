#include "Player.h"
#include "../Core/Core.h"

Player::Player() : Entity(ENTITYPOS( {0,0}, {0,0}, { 0,0 }, { 0,0 } ),
    EntityState(false),
    ENTITY_TYPE::Player)
{
    state = { false, 0, 0, false, Skill::None, false, Skill::None };
    pos = { 0 };
    skill = Skill::None;
}

Player::Player(PlayerState _state, ENTITYPOS _pos) : Entity(_pos, _state, ENTITY_TYPE::Player)
{
    state = _state;
    pos = _pos;
    pos.tForward = { 0,0 };
    skill = Skill::None;
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

}

void Player::CheckTile(Map* _map)
{
    if (_map->isTile(pos.tPos.x, pos.tPos.y, Tile::COIN))
    {
        state.score++;
        _map->SetMapTile(pos.tPos.x, pos.tPos.y, Tile::ROAD);

        SetSight(max(3, 100 * (_map->MapCoinCnt - state.score) / _map->MapCoinCnt / 2));

        if (_map->MapCoinCnt == state.score)
        {
            Core::Instance->ChangeScene(SCENE::WIN);
        }
    }
    if (_map->isTile(pos.tPos.x, pos.tPos.y, Tile::ITEM))
    {
        if (state.isHaveSkill)
            return;

        state.isHaveSkill = true;
        srand((unsigned int)time(nullptr));
        int rVal = rand() % (int)Skill::END;
        state.whatSkill = (Skill)rVal;
        _map->SetMapTile(pos.tPos.x, pos.tPos.y, Tile::ROAD);
    }
}

void Player::SetSight(int sight)
{
    state.maxSight = sight;
}

void Player::SetSkill(Skill skill)
{
    skill = skill;
}

bool Player::UseSkill()
{
    if (!state.isHaveSkill) return false;

    if (state.whatSkill == Skill::KILL)
    {
        state.usingSkill = Skill::KILL;
        state.isHaveSkill = false;
        state.isUsingSkill = true;
        return true;
    }
    else if (state.whatSkill == Skill::SIGHT)
    {
        state.usingSkill = Skill::SIGHT;
        state.isHaveSkill = false;
        state.isUsingSkill = true;
        return true;
    }
    else if (state.whatSkill == Skill::DASH)
    {
        state.usingSkill = Skill::DASH;
        state.isHaveSkill = false;
        state.isUsingSkill = true;
        return true;
    }
    return false;
}
