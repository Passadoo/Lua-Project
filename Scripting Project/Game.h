#pragma once

#include "Player.h"
#include "Obstacle.h"
#include "Map.h"
#include <iostream>

class Game
{
private:
	Entity** mObstacles;
	Player* mPlayer;
	int mNrOfObstacles;

public:
	Game();
	Game(Map &map);
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

