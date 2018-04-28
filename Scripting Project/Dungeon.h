#pragma once
#include "Room.h"

class Dungeon
{
private:
	Room ** mRooms;

	int mArrayLength;
	int mCurrentRoomX;
	int mCurrentRoomY;

	struct RoomInfo
	{
		string mFilename;
		bool mHasDoorUp = false;
		bool mHasDoorRight = false;
		bool mHasDoorDown = false;
		bool mHasDoorLeft = false;
	};

	vector<RoomInfo> mRoomInfo;

public:
	Dungeon();
	~Dungeon();

	Room& GetCurrentRoom();
	void LoadCurrentRoom();
	void LoadRoom(int pXIndex, int pYIndex);
	bool AddRoom();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

