#pragma once

#include <fstream>
#include <SFML\Graphics.hpp>
#include "Defined.h"
#include <vector>
#include <iostream>
#include "Player.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Door.h"

using namespace std;

class Map
{
private:
	static Defined::ObjectTypes** mObjectTypes;
	static int mNrOfObstacles;
	static int mNrOfEnemies;
	static int mNrOfDoors;
	static vector<char> mDirections;

	static	void fillGrid(const vector<string> & lines, const vector<char> & chars);
public:
	Map();
	~Map();

	static	bool ReadMap(const string & path);
	static	void setObjects(string filepath, Obstacle **& pObstacles, int & pNrOfObstacles, Enemy **& pEnemies, int & pNrOfEnemies,
		Door **& pDoors, int & pNrOfDoors);
};

