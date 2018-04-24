#include "Dungeon.h"



Dungeon::Dungeon()
{
	mArrayLength = 0;
}

Dungeon::Dungeon(int pNrOfRooms)
{
	ifstream ifs;
	char input;

	ifs.open("Resources/Rooms/RoomInfo.txt");

	if (ifs.fail())
	{
		std::cout << "Could not open RoomInfo.txt" << std:: endl;
	}

	vector<string> lines;
	vector<string> filepaths;
	vector<string> doorLocations;
	string word;

	while (!ifs.eof())
	{
		ifs >> word; //read filepath
		filepaths.push_back(word);
		ifs >> word; //read door locations in form of 4 ints
		doorLocations.push_back(word);
	}

	if (filepaths.size() > 0)
	{
		mArrayLength = filepaths.size();
	}


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


