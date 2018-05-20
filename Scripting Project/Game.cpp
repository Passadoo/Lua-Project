#include "Game.h"

void Game::playerUpdate(float dt)
{
	Vector2f nextPos;
	LuaManager::CallLuaFunc<void>("SetMoveInitFalse");

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		lua_playerMovement(Defined::RIGHT, nextPos);
		
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		lua_playerMovement(Defined::DOWN, nextPos);

	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		lua_playerMovement(Defined::LEFT, nextPos);

	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		lua_playerMovement(Defined::UP, nextPos);

	}

	if (LuaManager::CallLuaFunc<bool>("GetMoveInit"))
	{
		bool canMove = true;

		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfObstacles(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetObstacles()[i]->GetPos().x == nextPos.x && mDungeon->GetCurrentRoom().GetObstacles()[i]->GetPos().y == nextPos.y)
			{
				canMove = false;
			}
		}

		bool enteredDoor = false;

		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfDoors(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetDoors()[i]->GetPos().x == nextPos.x && mDungeon->GetCurrentRoom().GetDoors()[i]->GetPos().y == nextPos.y)
			{
				std::cout << "entered door" << std::endl;
				enteredDoor = true;
			}
		}

		if (enteredDoor)
		{
			roomUpdate();
		}
		else if (canMove)
		{
			mPlayer->SetPosition(nextPos);
		}
	}

	mPlayer->Update(dt);
}

void Game::roomUpdate()
{
	LuaManager::CallLuaFunc<void>("EnterRoom", (int)Defined::GRID_CELL_SIZE, (int)Defined::WORLD_WIDTH, (int)Defined::WORLD_HEIGHT);

	if (LuaManager::CallLuaFunc<bool>("GetEnteredDoorUp"))
	{
		if (!mDungeon->RoomUpExists())
		{
			if (mDungeon->AddRoomUp())
			{
				mDungeon->LoadCurrentRoom();
				Vector2f newLocation = mDungeon->GetCurrentRoomDownDoorLocation();
				if (newLocation.x >= 0.0f)
				{
					mPlayer->SetPosition(Vector2f(newLocation.x, newLocation.y - Defined::GRID_CELL_SIZE));
				}
			}
			else
			{
				std::cout << "No more rooms exist in this direction" << std::endl;
			}
		}
		else
		{
			if (mDungeon->UpRoomHasDownDoor())
			{
				mDungeon->SwitchRoomUp();
				Vector2f newLocation = mDungeon->GetCurrentRoomDownDoorLocation();
				if (newLocation.x >= 0.0f)
				{
					mPlayer->SetPosition(Vector2f(newLocation.x, newLocation.y - Defined::GRID_CELL_SIZE));
				}
			}
			else
			{
				std::cout << "A room exists but it does not have the required door" << std::endl;
			}
		}
	}
	if (LuaManager::CallLuaFunc<bool>("GetEnteredDoorRight"))
	{
		if (!mDungeon->RoomRightExists())
		{
			if (mDungeon->AddRoomRight())
			{
				mDungeon->LoadCurrentRoom();
				Vector2f newLocation = mDungeon->GetCurrentRoomLeftDoorLocation();
				if (newLocation.x >= 0.0f)
				{
					mPlayer->SetPosition(Vector2f(newLocation.x + Defined::GRID_CELL_SIZE, newLocation.y));
				}
			}
			else
			{
				std::cout << "No more rooms exist in this direction" << std::endl;
			}
		}
		else
		{
			if (mDungeon->RightRoomHasLeftDoor())
			{
				mDungeon->SwitchRoomRight();
				Vector2f newLocation = mDungeon->GetCurrentRoomLeftDoorLocation();
				if (newLocation.x >= 0.0f)
				{
					mPlayer->SetPosition(Vector2f(newLocation.x + Defined::GRID_CELL_SIZE, newLocation.y));
				}
			}
			else
			{
				std::cout << "A room exists but it does not have the required door" << std::endl;
			}
		}
	}
	if (LuaManager::CallLuaFunc<bool>("GetEnteredDoorDown"))
	{
		if (!mDungeon->RoomDownExists())
		{
			if (mDungeon->AddRoomDown())
			{
				mDungeon->LoadCurrentRoom();
				Vector2f newLocation = mDungeon->GetCurrentRoomUpDoorLocation();
				if (newLocation.x >= 0.0f)
				{
					mPlayer->SetPosition(Vector2f(newLocation.x, newLocation.y + Defined::GRID_CELL_SIZE));
				}
			}
			else
			{
				std::cout << "No more rooms exist in this direction" << std::endl;
			}
		}
		else
		{
			if (mDungeon->DownRoomHasUpDoor())
			{
				mDungeon->SwitchRoomDown();
				Vector2f newLocation = mDungeon->GetCurrentRoomUpDoorLocation();
				if (newLocation.x >= 0.0f)
				{
					mPlayer->SetPosition(Vector2f(newLocation.x, newLocation.y + Defined::GRID_CELL_SIZE));
				}
			}
			else
			{
				std::cout << "A room exists but it does not have the required door" << std::endl;
			}
		}
	}
	if (LuaManager::CallLuaFunc<bool>("GetEnteredDoorLeft"))
	{
		std::cout << "Entered door left" << std::endl;
		if (!mDungeon->RoomLeftExists())
		{
			if (mDungeon->AddRoomLeft())
			{
				mDungeon->LoadCurrentRoom();
				Vector2f newLocation = mDungeon->GetCurrentRoomRightDoorLocation();
				if (newLocation.x >= 0.0f)
				{
					mPlayer->SetPosition(Vector2f(newLocation.x - Defined::GRID_CELL_SIZE, newLocation.y));
				}
			}
			else
			{
				std::cout << "No more rooms exist in this direction" << std::endl;
			}
		}
		else
		{
			if (mDungeon->LeftRoomHasRightDoor())
			{
				mDungeon->SwitchRoomLeft();
				Vector2f newLocation = mDungeon->GetCurrentRoomRightDoorLocation();
				if (newLocation.x >= 0.0f)
				{
					mPlayer->SetPosition(Vector2f(newLocation.x - Defined::GRID_CELL_SIZE, newLocation.y));
				}
			}
			else
			{
				std::cout << "A room exists but it does not have the required door" << std::endl;
			}
		}
	}

	std::cout << "There are " << mDungeon->GetNrOfRemainingRooms() << " rooms remaining" << std::endl;
}

void Game::bulletUpdate(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (mNrOfBullets < 5)
		{
			mBullets[mNrOfBullets] = new Bullet(mPlayer->GetPos().x, mPlayer->GetPos().y, (Defined::eDirection)mPlayer->GetDirection());
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

void Game::enemyUpdate(float dt)
{

}

Game::Game()
{
	mBullets = new Bullet*[5];
	mNrOfBullets = 0;
	mPlayer = new Player(2, 2);
	mDungeon = new Dungeon();
	
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

Game::~Game()
{
	for (int i = 0; i < mNrOfBullets; i++)
	{
		delete mBullets[i];
	}
	delete[] mBullets;

	delete mPlayer;
	delete mDungeon;

	LuaManager::CloseLuaManager();
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

void Game::RestartGame()
{
	//Delete old
	for (int i = 0; i < mNrOfBullets; i++)
	{
		delete mBullets[i];
	}
	delete[] mBullets;
	delete mPlayer;
	delete mDungeon;
	LuaManager::CloseLuaManager();

	//Create new
	mBullets = new Bullet*[5];
	mNrOfBullets = 0;
	mPlayer = new Player(2, 2);
	mDungeon = new Dungeon();
	mCurrentState = ePLAYING;
	initLuaManager();
	mDungeon->LoadCurrentRoom();
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

void Game::Update(float dt)
{
	if (mCurrentState == ePLAYING)
	{
		mDungeon->Update(dt);
		playerUpdate(dt);
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

	LuaFunctionsWrapper::RegisterCFunction("SetDirection", mPlayer, &Player::SetDirection, _1);
	LuaFunctionsWrapper::RegisterCFunction("GetDirection", mPlayer, &Player::GetDirection);
	LuaFunctionsWrapper::RegisterCFunction("GetPosX", (Entity*&)mPlayer, &Player::GetPosX);
	LuaFunctionsWrapper::RegisterCFunction("GetPosY", (Entity*&)mPlayer, &Player::GetPosY);

	LuaFunctionsWrapper::RegisterCFunction("NoObstacle", mDungeon, &Dungeon::NoObstacle, _1, _2);
	LuaFunctionsWrapper::RegisterCFunction("NoEnemy", mDungeon, &Dungeon::NoEnemy, _1, _2);
	LuaFunctionsWrapper::RegisterCFunction("NoDoor", mDungeon, &Dungeon::NoDoor, _1, _2);

	LuaManager::LoadScript(Defined::LUA_ENEMY_PATH);
}

void Game::lua_playerMovement(int dir, Vector2f& pos)
{
	if (LuaManager::CallLuaFuncS<bool>("MovePlayer", 3, dir, Defined::GRID_CELL_SIZE))
	{
		pos = Vector2f(LuaManager::GetFloat(), LuaManager::GetFloat());
	}
}
