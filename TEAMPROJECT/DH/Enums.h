#pragma once

enum class Key
{
	UP, DOWN, LEFT, RIGHT, SPACE, ESC, FAIL, Q, E
};

enum class Menu
{
	START, INFO, QUIT, FAIL, TITLE
};

enum class SCENE
{
	TITLE, GAME, INFO, QUIT, DEAD, WIN, END
};

enum class Tile
{
	None = -1, WALL = 0, COIN, PLAYER_START, ITEM, ENEMY_SPAWN, BROKEN_WALL, ROAD, BEDROCK, END
};

enum class Direction
{
	NONE, RIGHT, LEFT, UP, DOWN
};

enum class SKILL
{
	None = -1, KILL, SIGHT, DASH, END
};

enum class ENTITY_TYPE
{
	None = 0, Player, Enemy
};