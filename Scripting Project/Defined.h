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
	static const string ROOM_INFO_PATH;
	static const string ROOMS_PATH;

	//Grid
	static int GRID_CELL_SIZE;
	static int WORLD_WIDTH;
	static int WORLD_HEIGHT;

	//Time
	static const float BULLET_SPEED;

	//Enemies
	static const int ENEMY_HEALTH;

	// Entity paths
	static const string OBSTACLE_PATH;
	static const string DOOR_PATH;
	static const string ENEMY_PATH;
	static const string PLAYER_PATH;
	static const string BULLET_PATH;

	// Script paths
	static const string LUA_TEST_PATH;
	static const string LUA_TEST2_PATH;

};

