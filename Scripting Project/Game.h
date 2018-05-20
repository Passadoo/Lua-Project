#pragma once

#include "Dungeon.h"
#include <iostream>
#include "Keyboard.h"

// Lua
#include "LuaFunctionsWrapper.h"

class Game : public ILuaMember
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

	MKeyboard* keyboard;
	void bulletUpdate(float dt);

	void RemoveBullet(int index);
	void RestartGame();

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

