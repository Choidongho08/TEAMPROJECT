#pragma once

enum class Key
{
	UP, DOWN, LEFT, RIGHT, SPACE, ESC, FAIL
};

enum class Menu
{
	START, INFO, QUIT, FAIL
};

enum class Scene
{
	TITLE, GAME, INFO, QUIT, DEAD, END
};

enum class Tile
{
	WALL = 0, COIN, PLAYER_START, ITEM, ENEMY_SPAWN, BROKEN_WALL, ROAD, END
};

enum class Direction
{
	NONE, RIGHT, LEFT, UP, DOWN
};

enum class Skill
{
	None, KILL, SIGHT, DASH, END
};