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
	WALL = 0, ROAD, PLAYER_START, ITEM, ENEMY, ENEMY_SPAWN, END
};

enum class Direction
{
	NONE, RIGHT, LEFT, UP, DOWN
};

enum class Skill
{
	None, KILL, SIGHT, DASH, END
};