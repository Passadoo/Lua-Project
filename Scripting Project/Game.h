#pragma once

#include "Dungeon.h"
#include <iostream>
#include "Keyboard.h"

// Lua
#include "LuaFunctionsWrapper.h"

class Game : public ILuaMember
{
private:
	Bullet ** mBullets;
	int mNrOfBullets;

	Player* mPlayer;

	Dungeon * mDungeon;

	MKeyboard* keyboard;
	void bulletUpdate(float dt);

	void RemoveBullet(int index);

	void initGame();
	void closeGame();

public:
	Game();
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt, RenderWindow& window);

	// Lua
	void initLuaManager();
	void lua_playerMovement(int dir, Vector2f& pos);
};

