#include "Game.h"

void Game::playerUpdate(float dt)
{
	Vector2f nextPos;
	LuaManager::CallLuaFunction("SetMoveInitFalse");

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

	LuaManager::CallLuaFunction("GetMoveInit", 0, 1);
	if (LuaManager::GetBool())
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
	lua_getglobal(LuaManager::GetCurrentState(), "EnterRoom");
	LuaManager::PushInteger(Defined::GRID_CELL_SIZE);
	LuaManager::PushInteger(Defined::WORLD_WIDTH);
	LuaManager::PushInteger(Defined::WORLD_HEIGHT);
	LuaManager::CallLuaFunction("EnterRoom", 3, 0);

	LuaManager::CallLuaFunction("GetEnteredDoorUp", 0, 1);
	if (LuaManager::GetBool())
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
			mDungeon->SwitchRoomUp();
			Vector2f newLocation = mDungeon->GetCurrentRoomDownDoorLocation();
			if (newLocation.x >= 0.0f)
			{
				mPlayer->SetPosition(Vector2f(newLocation.x, newLocation.y - Defined::GRID_CELL_SIZE));
			}
		}
	}
	LuaManager::CallLuaFunction("GetEnteredDoorRight", 0, 1);
	if (LuaManager::GetBool())
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
			mDungeon->SwitchRoomRight();
			Vector2f newLocation = mDungeon->GetCurrentRoomLeftDoorLocation();
			if (newLocation.x >= 0.0f)
			{
				mPlayer->SetPosition(Vector2f(newLocation.x + Defined::GRID_CELL_SIZE, newLocation.y));
			}
		}
	}
	LuaManager::CallLuaFunction("GetEnteredDoorDown", 0, 1);
	if (LuaManager::GetBool())
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
			mDungeon->SwitchRoomDown();
			Vector2f newLocation = mDungeon->GetCurrentRoomUpDoorLocation();
			if (newLocation.x >= 0.0f)
			{
				mPlayer->SetPosition(Vector2f(newLocation.x, newLocation.y + Defined::GRID_CELL_SIZE));
			}
		}
	}
	LuaManager::CallLuaFunction("GetEnteredDoorLeft", 0, 1);
	if (LuaManager::GetBool())
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
			mDungeon->SwitchRoomLeft();
			Vector2f newLocation = mDungeon->GetCurrentRoomRightDoorLocation();
			if (newLocation.x >= 0.0f)
			{
				mPlayer->SetPosition(Vector2f(newLocation.x - Defined::GRID_CELL_SIZE, newLocation.y));
			}
		}
	}
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
	mDungeon->LoadCurrentRoom();

	initLuaManager();
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

void Game::Draw(RenderWindow & window)
{
	for (int i = 0; i<mNrOfBullets; i++)
	{
		mBullets[i]->Draw(window);
	}

	mPlayer->Draw(window);
	mDungeon->Draw(window);
}

void Game::Update(float dt)
{
	mDungeon->Update(dt);
	playerUpdate(dt);
	bulletUpdate(dt);
}

void Game::initLuaManager()
{
	LuaManager::InitLuaManager();

	LuaManager::LoadScript(Defined::LUA_GAME_LOGIC_PATH);

	/*mPlayer->AddFunction<void, Player, int>("SetDirection", mPlayer, &Player::SetDirection);
	LuaFunctionsWrapper::AddCFunction<Player, void, int>(mPlayer);


	mPlayer->AddFunctionI<int, Player>("GetDirection", mPlayer, &Player::GetDirection);
	LuaFunctionsWrapper::AddCFunction<Player, int>(mPlayer);

	mPlayer->AddFunctionF<float, Player>("GetPosX", mPlayer, &Player::GetPosX);
	LuaFunctionsWrapper::AddCFunction<Player, float>(mPlayer);
	mPlayer->AddFunctionF<float, Player>("GetPosY", mPlayer, &Player::GetPosY);
	LuaFunctionsWrapper::AddCFunction<Player, float>(mPlayer);*/
}

void Game::lua_playerMovement(int dir, Vector2f& pos)
{
	lua_getglobal(LuaManager::GetCurrentState(), "MovePlayer");
	LuaManager::PushInteger(dir);
	LuaManager::PushInteger(Defined::GRID_CELL_SIZE);
	LuaManager::CallLuaFunction("MovePlayer", 2, 3);

	float y = LuaManager::GetFloat();
	float x = LuaManager::GetFloat();
	if (LuaManager::GetBool())
	{
		pos = Vector2f(x, y);
	}
}
