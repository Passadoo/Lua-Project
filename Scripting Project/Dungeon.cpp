#include "Dungeon.h"

Dungeon::Dungeon()
{
	ifstream ifs;
	char input;

	ifs.open("Resources/Rooms/RoomInfo.txt");

	if (ifs.fail())
	{
		std::cout << "Could not open RoomInfo.txt" << std:: endl;
	}

	vector<string> fileNames;
	vector<string> doorLocations;
	string word;

	while (!ifs.eof())
	{
		ifs >> word; //read filepath
		fileNames.push_back(word);
		ifs >> word; //read door locations in form of 4 ints
		doorLocations.push_back(word);
	}

	ifs.close();

	for (int i = 0; i < fileNames.size(); i++)
	{
		RoomInfo tempInfo;
		tempInfo.mFilename = fileNames[i];
		if (doorLocations[i].at(0) == '1')
		{
			tempInfo.mHasDoorUp = true;
		}
		if (doorLocations[i].at(1) == '1')
		{
			tempInfo.mHasDoorRight = true;
		}
		if (doorLocations[i].at(2) == '1')
		{
			tempInfo.mHasDoorDown = true;
		}
		if (doorLocations[i].at(3) == '1')
		{
			tempInfo.mHasDoorLeft = true;
		}
		mRoomInfo.push_back(tempInfo);
	}

	if (fileNames.size() > 0)
	{
		mArrayLength = (2 * fileNames.size()) - 1;
	}

	mCurrentRoomX = (mArrayLength - 1) / 2;
	mCurrentRoomY = (mArrayLength - 1) / 2;

	mRooms = new Room*[mArrayLength];
	for (int i = 0; i < mArrayLength; i++)
	{
		mRooms[i] = new Room[mArrayLength];
	}

	int index = -1;
	bool found = false;

	for (int i = 0; i < mRoomInfo.size() && !found; i++)
	{
		if (mRoomInfo[i].mFilename == "StartRoom.txt")
		{
			index = i;
			found = true;
		}
	}

	mRooms[mCurrentRoomX][mCurrentRoomY] = Room(mRoomInfo[index].mFilename, mRoomInfo[index].mHasDoorUp, mRoomInfo[index].mHasDoorRight, mRoomInfo[index].mHasDoorDown, mRoomInfo[index].mHasDoorLeft);
	mRoomInfo.erase(mRoomInfo.begin() + index);
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

Room Dungeon::GetCurrentRoom()
{
	std::cout << mRooms[mCurrentRoomX][mCurrentRoomY].Exists() << std::endl;
	return mRooms[mCurrentRoomX][mCurrentRoomY];
}

void Dungeon::LoadCurrentRoom()
{
	mRooms[mCurrentRoomX][mCurrentRoomY].LoadRoom();
}

void Dungeon::LoadRoom(int pXIndex, int pYIndex)
{
	mRooms[pXIndex][pYIndex].LoadRoom();
}

bool Dungeon::AddRoom()
{
	int roomIndex = -1;

	bool roomFound = false;

	if (mRooms[mCurrentRoomX][mCurrentRoomY].HasDoorUp() && !mRooms[mCurrentRoomX][mCurrentRoomY - 1].Exists()) 
	{
		for (int i = 0; i < mRoomInfo.size() && !roomFound; i++)
		{
			if (mRoomInfo[i].mHasDoorDown)
			{
				roomIndex = i;
				roomFound = true;
			}
		}
	}
	else if (mRooms[mCurrentRoomX][mCurrentRoomY].HasDoorRight())
	{

	}

	return false;
}

void Dungeon::Draw(RenderWindow & window)
{
	mRooms[mCurrentRoomX][mCurrentRoomY].Draw(window);

	/*for (int i = 0; i < mArrayLength; i++)
	{
		for (int j = 0; j < mArrayLength; j++)
		{
			if (mRooms[i][j].Exists())
			{
				mRooms[i][j].Draw(window);
			}
		}
	}*/
}

void Dungeon::Update(float dt)
{
	mRooms[mCurrentRoomX][mCurrentRoomY].Update(dt);
}


