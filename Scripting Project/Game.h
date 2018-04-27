#pragma once

#include "Room.h"
#include <iostream>

class Game
{
private:
	Bullet ** mBullets;
	int mNrOfBullets;

	Player* mPlayer;

	Room * mRoom;

	void playerUpdate(float dt);
	void bulletUpdate(float dt);
	void enemyUpdate(float dt);

	void RemoveBullet(int index);

public:
	Game();
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

