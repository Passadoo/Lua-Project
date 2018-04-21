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
	Bullet** mBullets;
	int mNrOfBullets;
	int mNrOfObstacles;

	void playerUpdate(float dt);
	void bulletUpdate(float dt);

	void RemoveBullet(int index);

public:
	Game();
	Game(Map &map);
	~Game();



	void Draw(RenderWindow &window);
	void Update(float dt);
};

