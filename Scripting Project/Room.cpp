#include "Room.h"



Room::Room()
{
}

Room::Room(string pFilePath)
{
	mFilePath = pFilePath;
	mHasDoorUp = false;
	mHasDoorRight = false;
	mHasDoorDown = false;
	mHasDoorLeft = false;
}


Room::~Room()
{
}

void Room::LoadRoom(Player* & pPlayer, Obstacle **& pObstacles, int & pNrOfObstacles, Enemy **& pEnemies, int & pNrOfEnemies,
	Door **& pDoors, int & pNrOfDoors)
{
	Map::setObjects(mFilePath, pPlayer, pObstacles, pNrOfObstacles, pEnemies, pNrOfEnemies, pDoors, pNrOfDoors);
}
