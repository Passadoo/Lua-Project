#pragma once

#include "Room.h"
#include <iostream>

class Game
{
private:
	Obstacle** mObstacles;
	Bullet** mBullets;
	Enemy** mEnemies;
	Door** mDoors;
	Player* mPlayer;

	Room* mRoom;

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
	Game(int pNothing);
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

