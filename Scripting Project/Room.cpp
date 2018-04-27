#include "Room.h"

Room::Room()
{
	mExists = false;
}

Room::Room(string pFilePath, bool pHasDoorUp, bool pHasDoorRight, bool pHasDoorDown, bool pHasDoorLeft)
{
	mFilePath = "Resources/Rooms/" + pFilePath;
	mHasDoorUp = pHasDoorUp;
	mHasDoorRight = pHasDoorRight;
	mHasDoorDown = pHasDoorDown;
	mHasDoorLeft = pHasDoorLeft;
	mExists = true;
}


Room::~Room()
{
	for (int i = 0; i< mNrOfObstacles; i++)
	{
		delete mObstacles[i];
	}
	delete[] mObstacles;

	delete mPlayer;

	for (int i = 0; i < mNrOfEnemies; i++)
	{
		delete mEnemies[i];
	}
	delete[] mEnemies;

	for (int i = 0; i < mNrOfDoors; i++)
	{
		delete mDoors[i];
	}
	delete[] mDoors;
}

Obstacle ** Room::GetObstacles()const
{
	return mObstacles;
}

Enemy ** Room::GetEnemies()const
{
	return mEnemies;
}

Door ** Room::GetDoors()const
{
	return mDoors;
}

int Room::GetNrOfObstacles() const
{
	return mNrOfObstacles;
}

int Room::GetNrOfEnemies() const
{
	return mNrOfEnemies;
}

int Room::GetNrOfDoors() const
{
	return mNrOfDoors;
}

bool Room::HasDoorUp() const
{
	return mHasDoorUp;
}

bool Room::HasDoorRight() const
{
	return mHasDoorRight;
}

bool Room::HasDoorDown() const
{
	return mHasDoorDown;
}

bool Room::HasDoorLeft() const
{
	return mHasDoorLeft;
}

bool Room::Exists() const
{
	return mExists;
}

void Room::RemoveEnemy(int index)
{
	if (mNrOfEnemies > index)
	{
		delete mEnemies[index];
		for (int i = index; i < mNrOfEnemies - 1; i++)
		{
			mEnemies[i] = mEnemies[i + 1];
		}
		mNrOfEnemies--;
	}
}

void Room::LoadRoom()
{
	Map::setObjects(mFilePath, mObstacles, mNrOfObstacles, mEnemies, mNrOfEnemies, mDoors, mNrOfDoors);
}

void Room::Draw(RenderWindow & window)
{
	for (int i = 0; i<mNrOfObstacles; i++)
	{
		mObstacles[i]->Draw(window);
	}

	for (int i = 0; i < mNrOfEnemies; i++)
	{
		mEnemies[i]->Draw(window);
	}

	for (int i = 0; i < mNrOfDoors; i++)
	{
		mDoors[i]->Draw(window);
	}
}

void Room::Update(float dt)
{
	for (int i = 0; i<mNrOfObstacles; i++)
	{
		mObstacles[i]->Update(dt);
	}

	for (int i = 0; i < mNrOfDoors; i++)
	{
		mDoors[i]->Update(dt);
	}

	//Update enemies
}
