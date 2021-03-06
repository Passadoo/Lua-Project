#include "Dungeon.h"

Dungeon::Dungeon()
{
	ifstream ifs;
	char input = ' ';

	ifs.open(Defined::ROOM_INFO_PATH);

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

	for (int i = 0; i < (int)fileNames.size(); i++)
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

	for (int i = 0; i < (int)mRoomInfo.size() && !found; i++)
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

Room& Dungeon::GetCurrentRoom()
{
	return mRooms[mCurrentRoomX][mCurrentRoomY];
}

void Dungeon::LoadCurrentRoom()
{
	std::cout << "Loading room at: " << mCurrentRoomX << ", " << mCurrentRoomY << std::endl;
	mRooms[mCurrentRoomX][mCurrentRoomY].LoadRoom();
}

void Dungeon::LoadRoom(int pXIndex, int pYIndex)
{
	mRooms[pXIndex][pYIndex].LoadRoom();
}

bool Dungeon::AddRoomUp()
{
	int roomIndex = -1;

	bool roomFound = false;

	if (mRooms[mCurrentRoomX][mCurrentRoomY].HasDoorUp() && !mRooms[mCurrentRoomX][mCurrentRoomY - 1].Exists()) 
	{
		for (int i = 0; i < (int)mRoomInfo.size() && !roomFound; i++)
		{
			if (mRoomInfo[i].mHasDoorDown)
			{
				roomIndex = i;
				roomFound = true;
			}
		}
	}

	if (roomIndex >= 0)
	{
		mRooms[mCurrentRoomX][mCurrentRoomY - 1] = Room(mRoomInfo[roomIndex].mFilename, mRoomInfo[roomIndex].mHasDoorUp, mRoomInfo[roomIndex].mHasDoorRight, mRoomInfo[roomIndex].mHasDoorDown, mRoomInfo[roomIndex].mHasDoorLeft);
		mCurrentRoomY = mCurrentRoomY - 1;
		mRoomInfo.erase(mRoomInfo.begin() + roomIndex);
	}


	return roomFound;
}

bool Dungeon::AddRoomRight()
{
	int roomIndex = -1;

	bool roomFound = false;

	if (mRooms[mCurrentRoomX][mCurrentRoomY].HasDoorRight() && !mRooms[mCurrentRoomX + 1][mCurrentRoomY].Exists())
	{
		for (int i = 0; i < (int)mRoomInfo.size() && !roomFound; i++)
		{
			if (mRoomInfo[i].mHasDoorLeft)
			{
				roomIndex = i;
				roomFound = true;
			}
		}
	}

	if (roomIndex >= 0)
	{
		mRooms[mCurrentRoomX + 1][mCurrentRoomY] = Room(mRoomInfo[roomIndex].mFilename, mRoomInfo[roomIndex].mHasDoorUp, mRoomInfo[roomIndex].mHasDoorRight, mRoomInfo[roomIndex].mHasDoorDown, mRoomInfo[roomIndex].mHasDoorLeft);
		mCurrentRoomX = mCurrentRoomX + 1;
		mRoomInfo.erase(mRoomInfo.begin() + roomIndex);
	}


	return roomFound;
}

bool Dungeon::AddRoomDown()
{
	int roomIndex = -1;

	bool roomFound = false;

	if (mRooms[mCurrentRoomX][mCurrentRoomY].HasDoorDown() && !mRooms[mCurrentRoomX][mCurrentRoomY + 1].Exists())
	{
		for (int i = 0; i < (int)mRoomInfo.size() && !roomFound; i++)
		{
			if (mRoomInfo[i].mHasDoorUp)
			{
				roomIndex = i;
				roomFound = true;
			}
		}
	}

	if (roomIndex >= 0)
	{
		mRooms[mCurrentRoomX][mCurrentRoomY + 1] = Room(mRoomInfo[roomIndex].mFilename, mRoomInfo[roomIndex].mHasDoorUp, mRoomInfo[roomIndex].mHasDoorRight, mRoomInfo[roomIndex].mHasDoorDown, mRoomInfo[roomIndex].mHasDoorLeft);
		mCurrentRoomY = mCurrentRoomY + 1;
		mRoomInfo.erase(mRoomInfo.begin() + roomIndex);
	}


	return roomFound;
}

bool Dungeon::AddRoomLeft()
{
	int roomIndex = -1;

	bool roomFound = false;

	if (mRooms[mCurrentRoomX][mCurrentRoomY].HasDoorLeft() && !mRooms[mCurrentRoomX - 1][mCurrentRoomY].Exists())
	{
		for (int i = 0; i < (int)mRoomInfo.size() && !roomFound; i++)
		{
			if (mRoomInfo[i].mHasDoorRight)
			{
				roomIndex = i;
				roomFound = true;
			}
		}
	}

	if (roomIndex >= 0)
	{
		mRooms[mCurrentRoomX - 1][mCurrentRoomY] = Room(mRoomInfo[roomIndex].mFilename, mRoomInfo[roomIndex].mHasDoorUp, mRoomInfo[roomIndex].mHasDoorRight, mRoomInfo[roomIndex].mHasDoorDown, mRoomInfo[roomIndex].mHasDoorLeft);
		mCurrentRoomX = mCurrentRoomX - 1;
		mRoomInfo.erase(mRoomInfo.begin() + roomIndex);
	}


	return roomFound;
}

bool Dungeon::RoomUpExists()
{
	return mRooms[mCurrentRoomX][mCurrentRoomY - 1].Exists();
}

bool Dungeon::RoomRightExists()
{
	return mRooms[mCurrentRoomX + 1][mCurrentRoomY].Exists();
}

bool Dungeon::RoomDownExists()
{
	return mRooms[mCurrentRoomX][mCurrentRoomY + 1].Exists();
}

bool Dungeon::RoomLeftExists()
{
	return mRooms[mCurrentRoomX - 1][mCurrentRoomY].Exists();
}

void Dungeon::SwitchRoomUp()
{
	mCurrentRoomY -= 1;
}

void Dungeon::SwitchRoomRight()
{
	mCurrentRoomX += 1;
}

void Dungeon::SwitchRoomDown()
{
	mCurrentRoomY += 1;
}

void Dungeon::SwitchRoomLeft()
{
	mCurrentRoomX -= 1;
}

bool Dungeon::LeftRoomHasRightDoor()
{
	if (mRooms[mCurrentRoomX - 1][mCurrentRoomY].HasDoorRight())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Dungeon::UpRoomHasDownDoor()
{
	if (mRooms[mCurrentRoomX][mCurrentRoomY - 1].HasDoorDown())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Dungeon::RightRoomHasLeftDoor()
{
	if (mRooms[mCurrentRoomX + 1][mCurrentRoomY].HasDoorLeft())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Dungeon::DownRoomHasUpDoor()
{
	if (mRooms[mCurrentRoomX][mCurrentRoomY + 1].HasDoorUp())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Dungeon::Draw(RenderWindow & window)
{
	mRooms[mCurrentRoomX][mCurrentRoomY].Draw(window);
}

void Dungeon::Update(float dt)
{
	mRooms[mCurrentRoomX][mCurrentRoomY].Update(dt);
}

bool Dungeon::NoObstacle(float x, float y)
{
	bool empty = true;
	for (int i = 0; i < GetCurrentRoom().GetNrOfObstacles(); i++)
	{
		if (GetCurrentRoom().GetObstacles()[i]->GetPos() == sf::Vector2f(x, y))
			empty = false;
	}
	return empty;
}

bool Dungeon::NoEnemy(float x, float y)
{
	bool empty = true;
	for (int i = 0; i < GetCurrentRoom().GetNrOfEnemies(); i++)
	{
		if (GetCurrentRoom().GetEnemies()[i]->GetPos() == sf::Vector2f(x, y))
			empty = false;
	}
	return empty;
}

bool Dungeon::NoDoor(float x, float y)
{
	bool empty = true;
	for (int i = 0; i < GetCurrentRoom().GetNrOfDoors(); i++)
	{
		if (GetCurrentRoom().GetDoors()[i]->GetPos() == sf::Vector2f(x, y))
			empty = false;
	}
	return empty;
}

float Dungeon::GetYDoorX(float x)
{
	float y = -1;
	for (int i = 0; i < GetCurrentRoom().GetNrOfDoors(); i++)
	{
		if (GetCurrentRoom().GetDoors()[i]->GetPosX() == x)
			y = GetCurrentRoom().GetDoors()[i]->GetPosY();
	}
	return y;
}

float Dungeon::GetXDoorY(float y)
{
	float x = -1;
	for (int i = 0; i < GetCurrentRoom().GetNrOfDoors(); i++)
	{
		if (GetCurrentRoom().GetDoors()[i]->GetPosY() == y)
			x = GetCurrentRoom().GetDoors()[i]->GetPosX();
	}
	return x;
}

int Dungeon::GetNrOfRemainingRooms()
{
	return mRoomInfo.size();
}


