#pragma once
#include <string>
#include "Map.h"

using namespace std;


class Room
{
private:
	string mFilePath;
	bool mHasDoorUp;
	bool mHasDoorRight;
	bool mHasDoorDown;
	bool mHasDoorLeft;

public:
	Room();
	Room(string pFilePath);
	~Room();

	void LoadRoom(Player* & pPlayer, Obstacle **& pObstacles, int & pNrOfObstacles, Enemy **& pEnemies, int & pNrOfEnemies,
		Door **& pDoors, int & pNrOfDoors);
};

