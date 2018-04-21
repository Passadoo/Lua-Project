#pragma once

#include "Player.h"
#include "Obstacle.h"
#include "Map.h"
#include <iostream>

class Game
{
private:
	Obstacle** mObstacles;
	Bullet** mBullets;
	Enemy** mEnemies;
	Player* mPlayer;
	int mNrOfBullets;
	int mNrOfObstacles;
	int mNrOfEnemies;

	void playerUpdate(float dt);
	void bulletUpdate(float dt);
	void enemyUpdate(float dt);

	void RemoveBullet(int index);

public:
	Game();
	Game(Map &map);
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

