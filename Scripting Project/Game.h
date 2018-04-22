#pragma once

#include "Map.h"
#include <iostream>

class Game
{
private:
	Obstacle** mObstacles;
	Bullet** mBullets;
	Enemy** mEnemies;
	Door** mDoors;
	Player* mPlayer;

	int mNrOfBullets;
	int mNrOfObstacles;
	int mNrOfEnemies;
	int mNrOfDoors;

	void playerUpdate(float dt);
	void bulletUpdate(float dt);
	void enemyUpdate(float dt);

	void RemoveBullet(int index);
	void RemoveEnemy(int index);

public:
	Game();
	Game(Map &map);
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

