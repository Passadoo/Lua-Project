#pragma once

#include "Dungeon.h"
#include <iostream>

// Lua
#include "LuaManager.h"
#include "LuaFunctionsWrapper.h"

class Game
{
private:
	Bullet ** mBullets;
	int mNrOfBullets;

	Player* mPlayer;

	Dungeon * mDungeon;

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

	// Lua
	void initLuaManager();
	void lua_playerMovement(int dir, Vector2f& pos);
};

