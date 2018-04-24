#pragma once
#include "Room.h"

class Dungeon
{
private:
	Room ** mRooms;
	int mArrayLength;

public:
	Dungeon();
	Dungeon(int pNrOfRooms);
	~Dungeon();
};

