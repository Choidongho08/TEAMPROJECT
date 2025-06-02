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
	WALL = '0', ROAD, START, GOAL, BOMB, FLASH_BOMB, EXTRA_BOMB, SLIME, PUSH, END
};