#pragma once

#include <fstream>
#include <SFML\Graphics.hpp>
#include "Defined.h"
#include <vector>
#include <iostream>
#include "Player.h"
#include "Obstacle.h"
#include "Enemy.h"

using namespace std;

class Map
{
private:
	Defined::ObjectTypes** mObjectTypes;
	int mNrOfObstacles;
	int mNrOfEnemies;
	vector<char> mDirections;

	void fillGrid(const vector<string> & lines, const vector<char> & chars);
public:
	Map();
	~Map();

	bool ReadMap(const string & path);
	void setObjects(Player* & pPlayer, Obstacle **& pObstacles, int & pNrOfObstacles, Enemy **& pEnemies, int & pNrOfEnemies);
};

