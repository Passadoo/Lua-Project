#pragma once

#include <fstream>
#include <SFML\Graphics.hpp>
#include "Defined.h"
#include <vector>
#include <iostream>
#include "Player.h"
#include "Obstacle.h"

using namespace std;

class Map
{
private:
	vector<sf::Vector2i> mObstaclePositions;
	Defined::ObjectTypes** mObjectTypes;
	int mNrOfObstacles;


	void fillGrid(const vector<string> & lines, const vector<char> & chars);
public:
	Map();
	~Map();

	bool ReadMap(const string & path);
	void setObjects(Player* & pPlayer, Entity **& pObstacles, int & pNrOfObstacles);
};

