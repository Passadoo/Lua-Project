#pragma once

#include "Dungeon.h"
#include <iostream>

class Game
{
private:
	Bullet ** mBullets;
	int mNrOfBullets;

	Player* mPlayer;

	Dungeon * mDungeon;
	//Room * mRoom;

	void playerUpdate(float dt);
	void roomUpdate();
	void bulletUpdate(float dt);
	void enemyUpdate(float dt);

	void RemoveBullet(int index);

public:
	Game();
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

