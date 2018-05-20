#pragma once
#include "Room.h"
#include "ILuaMember.h"

class Dungeon : public ILuaMember
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

	bool AddRoomUp();
	bool AddRoomRight();
	bool AddRoomDown();
	bool AddRoomLeft();

	bool RoomUpExists();
	bool RoomRightExists();
	bool RoomDownExists();
	bool RoomLeftExists();

	void SwitchRoomUp();
	void SwitchRoomRight();
	void SwitchRoomDown();
	void SwitchRoomLeft();

	bool LeftRoomHasRightDoor();
	bool UpRoomHasDownDoor();
	bool RightRoomHasLeftDoor();
	bool DownRoomHasUpDoor();

	void Draw(RenderWindow &window);
	void Update(float dt);

	bool NoObstacle(float x, float y);
	bool NoEnemy(float x, float y);
	bool NoDoor(float x, float y);

	float GetYDoorX(float x);
	float GetXDoorY(float y);

	int GetNrOfRemainingRooms();
};

