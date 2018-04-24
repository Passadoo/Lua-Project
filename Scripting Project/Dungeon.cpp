#include "Dungeon.h"



Dungeon::Dungeon()
{
	mArrayLength = 0;
}

Dungeon::Dungeon(int pNrOfRooms)
{
	mArrayLength = (2 * pNrOfRooms) + 1;

	mRooms = new Room*[mArrayLength];
	for (int i = 0; i < mArrayLength; i++)
	{
		mRooms[i] = new Room[mArrayLength];
	}
}


Dungeon::~Dungeon()
{
	for (int i = 0; i < mArrayLength; i++)
	{
		if (mRooms[i])
		{
			delete[] mRooms[i];
		}
	}
	delete[] mRooms;
}


