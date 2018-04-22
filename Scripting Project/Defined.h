#pragma once

#include <string>

using namespace std;

class Defined
{
public:
	//Object
	enum ObjectTypes { AIR = 0, PLAYER, OBSTACLE, ENEMY, DOOR};

	//Direction
	enum eDirection { UP = 0, DOWN, LEFT, RIGHT };
	
	//Window
	static unsigned int WINDOW_WIDTH;
	static unsigned int WINDOW_HEIGHT;

	//Map
	static const string MAP_PATH;

	//Grid
	static int GRID_CELL_SIZE;
	static int WORLD_WIDTH;
	static int WORLD_HEIGHT;

	//Time
	static const float BULLET_SPEED;

	//Enemies
	static const int ENEMY_HEALTH;





};

