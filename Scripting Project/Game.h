#pragma once

#include "Dungeon.h"
#include <iostream>

// Lua
#include "LuaFunctionsWrapper.h"

class Game
{
private:
	enum eGameState
	{
		ePLAYING = 0, eWON, eLOST
	};

	Bullet ** mBullets;
	int mNrOfBullets;
	Player* mPlayer;
	Dungeon * mDungeon;
	eGameState mCurrentState;
	sf::Texture mWinTexture;
	sf::Sprite mWinSprite;
	sf::Texture mLoseTexture;
	sf::Sprite mLoseSprite;

	void playerUpdate(float dt);
	void roomUpdate();
	void bulletUpdate(float dt);
	void enemyUpdate(float dt);

	void RemoveBullet(int index);
	void RestartGame();

public:
	Game();
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt);

	// Lua
	void initLuaManager();
	void lua_playerMovement(int dir, Vector2f& pos);
};

