#include "Game.h"

void Game::bulletUpdate(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (mNrOfBullets < 5)
		{
			mBullets[mNrOfBullets] = new Bullet((int)mPlayer->GetPos().x, (int)mPlayer->GetPos().y, (Defined::eDirection)mPlayer->GetDirection());
			mNrOfBullets++;
		}
	}

	Vector2f nextPos;
	Defined::eDirection bulletDirection;

	for (int i = 0; i < mNrOfBullets; i++)
	{
		bulletDirection = mBullets[i]->GetDirection();
		if (bulletDirection == Defined::UP)
		{
			nextPos = Vector2f(mBullets[i]->GetPos().x, mBullets[i]->GetPos().y - Defined::GRID_CELL_SIZE);
		}
		else if (bulletDirection == Defined::RIGHT)
		{
			nextPos = Vector2f(mBullets[i]->GetPos().x + Defined::GRID_CELL_SIZE, mBullets[i]->GetPos().y);
		}
		else if (bulletDirection == Defined::LEFT)
		{
			nextPos = Vector2f(mBullets[i]->GetPos().x - Defined::GRID_CELL_SIZE, mBullets[i]->GetPos().y);
		}
		else
		{
			nextPos = Vector2f(mBullets[i]->GetPos().x, mBullets[i]->GetPos().y + Defined::GRID_CELL_SIZE);
		}

		bool noWall = true;

		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfObstacles(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetObstacles()[i]->GetPos().x == nextPos.x && mDungeon->GetCurrentRoom().GetObstacles()[i]->GetPos().y == nextPos.y)
			{
				noWall = false;
			}
		}

		// Remove bullet if hit a door
		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfDoors(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetDoors()[i]->GetPos().x == nextPos.x && mDungeon->GetCurrentRoom().GetDoors()[i]->GetPos().y == nextPos.y)
			{
				noWall = false;
			}
		}

		bool noEnemy = true;
		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfEnemies(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetEnemies()[i]->GetPos().x == nextPos.x && mDungeon->GetCurrentRoom().GetEnemies()[i]->GetPos().y == nextPos.y)
			{
				noEnemy = false;
				mDungeon->GetCurrentRoom().GetEnemies()[i]->TakeDamage();
				if (mDungeon->GetCurrentRoom().GetEnemies()[i]->GetHealth() <= 0)
				{
					mDungeon->GetCurrentRoom().RemoveEnemy(i);
				}
			}
		}

		if (noWall && noEnemy)
		{
			mBullets[i]->Update(dt);
		}
		else
		{
			RemoveBullet(i);
		}
	}
}

Game::Game()
{
	initGame();
}

Game::~Game()
{
	closeGame();
}

void Game::RemoveBullet(int index)
{
	if (mNrOfBullets > index)
	{
		delete mBullets[index];
		for (int i = index; i < mNrOfBullets - 1; i++)
		{
			mBullets[i] = mBullets[i + 1];
		}
		mNrOfBullets--;
	}
}

void Game::initGame()
{
	mBullets = new Bullet*[5];
	mNrOfBullets = 0;
	mPlayer = new Player(2, 2);
	mDungeon = new Dungeon();
	keyboard = new MKeyboard();
	
	mCurrentState = ePLAYING;

	if(!mWinTexture.loadFromFile("Resources/WinTexture.png"))
	{
		std::cout << "WinTexture could not be loaded" << std::endl;
	}
	if (!mLoseTexture.loadFromFile("Resources/LoseTexture.png"))
	{
		std::cout << "LoseTexture could not be loaded" << std::endl;
	}

	mWinSprite.setTexture(mWinTexture);
	mWinSprite.setPosition(200.0f, 200.0f);
	mLoseSprite.setTexture(mLoseTexture);
	mLoseSprite.setPosition(200.0f, 200.0f);

	initLuaManager();

	mDungeon->LoadCurrentRoom();
}

void Game::closeGame()
{
	for (int i = 0; i < mNrOfBullets; i++)
	{
		delete mBullets[i];
	}
	delete[] mBullets;

	delete mPlayer;
	delete mDungeon;
	delete keyboard;

	LuaManager::CloseLuaManager();
}

void Game::RestartGame()
{
	//Delete old
	closeGame();
	//Create new
	initGame();
}

void Game::Draw(RenderWindow & window)
{
	if (mCurrentState == ePLAYING)
	{
		for (int i = 0; i < mNrOfBullets; i++)
		{
			mBullets[i]->Draw(window);
		}

		mPlayer->Draw(window);
		mDungeon->Draw(window);
	}
	else if (mCurrentState == eWON)
	{
		window.draw(mWinSprite);
	}
	else if (mCurrentState == eLOST)
	{
		window.draw(mLoseSprite);
	}
}

void Game::Update(float dt, RenderWindow& window)
{
	if (mCurrentState == ePLAYING)
	{
		mDungeon->Update(dt);
		LuaManager::CallLuaFunc<void>("UpdatePlayer", Defined::GRID_CELL_SIZE, (int)Defined::WORLD_WIDTH, (int)Defined::WORLD_HEIGHT);
		mPlayer->Update(dt);
		bulletUpdate(dt);

		if (mDungeon->GetNrOfRemainingRooms() <= 0)
		{
			mCurrentState = eWON;
		}
		
		bool hitEnemy = false;
		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfEnemies(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetEnemies()[i]->GetPosX() == mPlayer->GetPosX() && mDungeon->GetCurrentRoom().GetEnemies()[i]->GetPosY() == mPlayer->GetPosY())
			{
				hitEnemy = true;
			}
		}
		if (hitEnemy)
			mCurrentState = eLOST;

	}
	else if (mCurrentState == eWON)
	{
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			RestartGame();
		}
	}
	else if (mCurrentState == eLOST)
	{
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			RestartGame();
		}
	}
}

void Game::initLuaManager()
{
	LuaManager::InitLuaManager();

	LuaManager::LoadScript(Defined::LUA_GAME_LOGIC_PATH);

	LuaFunctionsWrapper::RegisterCFunction("SetPosition", mPlayer, &Player::SetPosition, _1, _2);
	LuaFunctionsWrapper::RegisterCFunction("SetDirection", mPlayer, &Player::SetDirection, _1);
	LuaFunctionsWrapper::RegisterCFunction("GetDirection", mPlayer, &Player::GetDirection);
	LuaFunctionsWrapper::RegisterCFunction("GetPosX", (Entity*)mPlayer, &Player::GetPosX);
	LuaFunctionsWrapper::RegisterCFunction("GetPosY", (Entity*)mPlayer, &Player::GetPosY);

	LuaFunctionsWrapper::RegisterCFunction("NoObstacle", mDungeon, &Dungeon::NoObstacle, _1, _2);
	LuaFunctionsWrapper::RegisterCFunction("NoEnemy", mDungeon, &Dungeon::NoEnemy, _1, _2);
	LuaFunctionsWrapper::RegisterCFunction("NoDoor", mDungeon, &Dungeon::NoDoor, _1, _2);

	LuaFunctionsWrapper::RegisterCFunction("IsKeyPressed", keyboard, &MKeyboard::IsKeyPressed, _1);

	// Functions for update the position of the player when entering a room
	LuaFunctionsWrapper::RegisterCFunction("RoomUpExists", mDungeon, &Dungeon::RoomUpExists);
	LuaFunctionsWrapper::RegisterCFunction("RoomRightExists", mDungeon, &Dungeon::RoomRightExists);
	LuaFunctionsWrapper::RegisterCFunction("RoomLeftExists", mDungeon, &Dungeon::RoomLeftExists);
	LuaFunctionsWrapper::RegisterCFunction("RoomDownExists", mDungeon, &Dungeon::RoomDownExists);

	LuaFunctionsWrapper::RegisterCFunction("AddRoomUp", mDungeon, &Dungeon::AddRoomUp);
	LuaFunctionsWrapper::RegisterCFunction("AddRoomRight", mDungeon, &Dungeon::AddRoomRight);
	LuaFunctionsWrapper::RegisterCFunction("AddRoomLeft", mDungeon, &Dungeon::AddRoomLeft);
	LuaFunctionsWrapper::RegisterCFunction("AddRoomDown", mDungeon, &Dungeon::AddRoomDown);

	LuaFunctionsWrapper::RegisterCFunction("LoadCurrentRoom", mDungeon, &Dungeon::LoadCurrentRoom);

	LuaFunctionsWrapper::RegisterCFunction("UpRoomHasDownDoor", mDungeon, &Dungeon::UpRoomHasDownDoor);
	LuaFunctionsWrapper::RegisterCFunction("SwitchRoomUp", mDungeon, &Dungeon::SwitchRoomUp);
	LuaFunctionsWrapper::RegisterCFunction("RightRoomHasLeftDoor", mDungeon, &Dungeon::RightRoomHasLeftDoor);
	LuaFunctionsWrapper::RegisterCFunction("SwitchRoomRight", mDungeon, &Dungeon::SwitchRoomRight);
	LuaFunctionsWrapper::RegisterCFunction("DownRoomHasUpDoor", mDungeon, &Dungeon::DownRoomHasUpDoor);
	LuaFunctionsWrapper::RegisterCFunction("SwitchRoomDown", mDungeon, &Dungeon::SwitchRoomDown);
	LuaFunctionsWrapper::RegisterCFunction("LeftRoomHasRightDoor", mDungeon, &Dungeon::LeftRoomHasRightDoor);
	LuaFunctionsWrapper::RegisterCFunction("SwitchRoomLeft", mDungeon, &Dungeon::SwitchRoomLeft);

	LuaFunctionsWrapper::RegisterCFunction("GetYDoorX", mDungeon, &Dungeon::GetYDoorX, _1);
	LuaFunctionsWrapper::RegisterCFunction("GetXDoorY", mDungeon, &Dungeon::GetXDoorY, _1);

	LuaFunctionsWrapper::RegisterCFunction("GetNrOfRemainingRooms", mDungeon, &Dungeon::GetNrOfRemainingRooms);

	LuaManager::LoadScript(Defined::LUA_ENEMY_PATH);
}

void Game::lua_playerMovement(int dir, Vector2f& pos)
{
	if (LuaManager::CallLuaFuncS<bool>("MovePlayer", 3, dir, Defined::GRID_CELL_SIZE))
	{
		pos = Vector2f(LuaManager::GetFloat(), LuaManager::GetFloat());
	}
}
