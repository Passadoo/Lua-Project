#pragma once

#include <string>

using namespace std;

class Defined
{
public:
	
	//Window
	static unsigned int WINDOW_WIDTH;
	static unsigned int WINDOW_HEIGHT;

	//Map
	static const string MAP_PATH;

	//Grid
	static int GRID_CELL_SIZE;
	static int WORLD_WIDTH;
	static int WORLD_HEIGHT;

	//Object
	enum ObjectTypes{AIR = 0, PLAYER, OBSTACLE, ENEMY};
	struct Object
	{
		ObjectTypes type;
	};

};

