#pragma once
#include <string>
#include "Map.h"

#include "LuaFunctionsWrapper.h"

using namespace std;


class Room
{
private:
	Obstacle ** mObstacles;
	Enemy** mEnemies;
	Door** mDoors;

	int mNrOfObstacles;
	int mNrOfEnemies;
	int mNrOfDoors;

	string mFilePath;
	bool mHasDoorUp;
	bool mHasDoorRight;
	bool mHasDoorDown;
	bool mHasDoorLeft;
	bool mExists;

	static int luaSetInt(lua_State * pL);
	static int luaSetPosition(lua_State * pL);
	static int luaGetFloat(lua_State * pL);
	static int luaSetFloat(lua_State * pL);

public:
	Room();
	Room(string pFilePath, bool pHasDoorUp, bool pHasDoorRight, bool pHasDoorDown, bool pHasDoorLeft);
	~Room();

	Obstacle **& GetObstacles();
	Enemy **& GetEnemies();
	Door **& GetDoors();

	int GetNrOfObstacles();
	int GetNrOfEnemies();
	int GetNrOfDoors();

	bool HasDoorUp()const;
	bool HasDoorRight()const;
	bool HasDoorDown()const;
	bool HasDoorLeft()const;

	bool Exists()const;

	void RemoveEnemy(int index);
	void LoadRoom();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

