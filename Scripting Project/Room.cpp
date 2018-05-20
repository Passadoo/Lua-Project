#include "Room.h"

int Room::luaSetInt(lua_State * pL)
{
	std::string function = LuaManager::GetString();
	std::string luaObject = LuaManager::GetString();

	int dir = LuaManager::GetInteger();

	ILuaMember* luaMember = LuaManager::GetObjectPtr<ILuaMember>(luaObject);

	luaMember->CallMemFunc<void>(LuaFunctionsWrapper::GenerateFuncName(function, luaMember), std::forward<int>(dir));
	return 0;
}

int Room::luaSetPosition(lua_State * pL)
{
	std::string function = LuaManager::GetString();
	std::string luaObject = LuaManager::GetString();

	float y = LuaManager::GetFloat();
	float x = LuaManager::GetFloat();

	ILuaMember* luaMember = LuaManager::GetObjectPtr<ILuaMember>(luaObject);

	luaMember->CallMemFunc<void>(LuaFunctionsWrapper::GenerateFuncName(function, luaMember), std::forward<float>(x), std::forward<float>(y));
	return 0;
}

int Room::luaGetFloat(lua_State * pL)
{
	std::string function = LuaManager::GetString();
	std::string luaObject = LuaManager::GetString();

	ILuaMember* luaMember = LuaManager::GetObjectPtr<ILuaMember>(luaObject);

	LuaManager::push(LuaManager::GetCurrentState(), luaMember->CallMemFunc<float>(LuaFunctionsWrapper::GenerateFuncName(function, luaMember)));
	return 1;
}

int Room::luaSetFloat(lua_State * pL)
{
	std::string function = LuaManager::GetString();
	std::string luaObject = LuaManager::GetString();

	float f = LuaManager::GetFloat();

	ILuaMember* luaMember = LuaManager::GetObjectPtr<ILuaMember>(luaObject);

	luaMember->CallMemFunc<void>(LuaFunctionsWrapper::GenerateFuncName(function, luaMember), std::forward<float>(f));
	return 0;
}

Room::Room()
{
	mObstacles = nullptr;
	mEnemies = nullptr;
	mDoors = nullptr;

	mNrOfObstacles = 0;
	mNrOfEnemies = 0;
	mNrOfDoors = 0;

	mExists = false;
}

Room::Room(string pFilePath, bool pHasDoorUp, bool pHasDoorRight, bool pHasDoorDown, bool pHasDoorLeft)
{
	mFilePath = "Resources/Rooms/" + pFilePath;
	mHasDoorUp = pHasDoorUp;
	mHasDoorRight = pHasDoorRight;
	mHasDoorDown = pHasDoorDown;
	mHasDoorLeft = pHasDoorLeft;
	mExists = true;

	mObstacles = nullptr;
	mEnemies = nullptr;
	mDoors = nullptr;

	mNrOfObstacles = 0;
	mNrOfEnemies = 0;
	mNrOfDoors = 0;
}


Room::~Room()
{
	for (int i = 0; i< mNrOfObstacles; i++)
	{
		delete mObstacles[i];
	}
	delete[] mObstacles;

	for (int i = 0; i < mNrOfEnemies; i++)
	{
		delete mEnemies[i];
	}
	delete[] mEnemies;

	for (int i = 0; i < mNrOfDoors; i++)
	{
		delete mDoors[i];
	}
	delete[] mDoors;
}

Obstacle **& Room::GetObstacles()
{
	return mObstacles;
}

Enemy **& Room::GetEnemies()
{
	return mEnemies;
}

Door **& Room::GetDoors()
{
	return mDoors;
}

int Room::GetNrOfObstacles() 
{
	return mNrOfObstacles;
}

int Room::GetNrOfEnemies() 
{
	return mNrOfEnemies;
}

int Room::GetNrOfDoors() 
{
	return mNrOfDoors;
}

bool Room::HasDoorUp() const
{
	return mHasDoorUp;
}

bool Room::HasDoorRight() const
{
	return mHasDoorRight;
}

bool Room::HasDoorDown() const
{
	return mHasDoorDown;
}

bool Room::HasDoorLeft() const
{
	return mHasDoorLeft;
}

bool Room::Exists() const
{
	return mExists;
}

void Room::RemoveEnemy(int index)
{
	if (mNrOfEnemies > index)
	{
		delete mEnemies[index];
		for (int i = index; i < mNrOfEnemies - 1; i++)
		{
			mEnemies[i] = mEnemies[i + 1];
		}
		mNrOfEnemies--;
	}
}

void Room::LoadRoom()
{
	Map::setObjects(mFilePath, mObstacles, mNrOfObstacles, mEnemies, mNrOfEnemies, mDoors, mNrOfDoors);

	for (int i = 0; i < mNrOfEnemies; i++)
	{
		LuaFunctionsWrapper::RegisterObject(mEnemies[i]);
		luaL_Reg functionList[] = { 
			{ "SetEnemyInt", luaSetInt },
			{ "SetEnemyPosition", luaSetPosition },
			{ "GetEnemyFloat", luaGetFloat },
			{ "SetEnemyFloat", luaSetFloat },
			{ NULL, NULL } 
		};
		LuaManager::RegisterObjectFunctions(mEnemies[i]->GetLuaObject(), functionList);

		LuaFunctionsWrapper::RegisterCFunction(LuaFunctionsWrapper::GenerateFuncName("SetDirection", mEnemies[i]), mEnemies[i], &Enemy::SetDirection, _1);
		LuaFunctionsWrapper::RegisterCFunction(LuaFunctionsWrapper::GenerateFuncName("SetPosition", mEnemies[i]), mEnemies[i], &Enemy::SetPosition, _1, _2);
		LuaFunctionsWrapper::RegisterCFunction(LuaFunctionsWrapper::GenerateFuncName("GetPosX", mEnemies[i]), (Entity*&)mEnemies[i], &Enemy::GetPosX);
		LuaFunctionsWrapper::RegisterCFunction(LuaFunctionsWrapper::GenerateFuncName("GetPosY", mEnemies[i]), (Entity*&)mEnemies[i], &Enemy::GetPosY);
		LuaFunctionsWrapper::RegisterCFunction(LuaFunctionsWrapper::GenerateFuncName("SetTime", mEnemies[i]), mEnemies[i], &Enemy::SetTime, _1);
		LuaFunctionsWrapper::RegisterCFunction(LuaFunctionsWrapper::GenerateFuncName("GetTime", mEnemies[i]), mEnemies[i], &Enemy::GetTime);
	}
}

void Room::Draw(RenderWindow & window)
{
	for (int i = 0; i < mNrOfObstacles; i++)
	{
		mObstacles[i]->Draw(window);
	}

	for (int i = 0; i < mNrOfEnemies; i++)
	{
		mEnemies[i]->Draw(window);
	}

	for (int i = 0; i < mNrOfDoors; i++)
	{
		mDoors[i]->Draw(window);
	}
}

void Room::Update(float dt)
{
	for (int i = 0; i<mNrOfObstacles; i++)
	{
		mObstacles[i]->Update(dt);
	}

	for (int i = 0; i < mNrOfDoors; i++)
	{
		mDoors[i]->Update(dt);
	}

	for (int i = 0; i < mNrOfEnemies; i++)
	{
		LuaManager::CallLuaFunc<void>("UpdateEnemy", mEnemies[i], mEnemies[i]->GetLuaObject(), Defined::GRID_CELL_SIZE, dt);
		mEnemies[i]->Update(dt);
	}
}
