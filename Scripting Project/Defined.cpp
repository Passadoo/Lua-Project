#include "Defined.h"

const bool Defined::DEBUG = false;

//Window
unsigned int Defined::WINDOW_WIDTH = 800;
unsigned int Defined::WINDOW_HEIGHT = 600;

//Map
const string Defined::MAP_PATH = "Resources/Rooms/StartRoom.txt";
const string Defined::ROOM_INFO_PATH = "Resources/Rooms/roomInfo.txt";
const string Defined::ROOMS_PATH = "Resources/Rooms/";

//Grid
int Defined::GRID_CELL_SIZE = 40; // 20 x 15 grid squares, each grid square 40 x 40 pixels large
int Defined::WORLD_WIDTH = 20; //20 grid cells wide
int Defined::WORLD_HEIGHT = 15; // 15 grid cells tall

//Time
const float Defined::BULLET_SPEED = 0.5;

//Enemies
const int Defined::ENEMY_HEALTH = 3;


// Entity paths
const string Defined::OBSTACLE_PATH = "Resources/Obstacle.png";
const string Defined::DOOR_PATH = "Resources/Door.png";
const string Defined::ENEMY_PATH = "Resources/Enemy.png";
const string Defined::PLAYER_PATH = "Resources/Player.png";
const string Defined::BULLET_PATH = "Resources/SmallBullet.png";


// Script paths
const string Defined::LUA_TEST_PATH = "Resources/Lua/test.lua";
const string Defined::LUA_TEST2_PATH = "Resources/Lua/test2.lua";
const string Defined::LUA_EDITOR_PATH = "Resources/Lua/editor.lua";
const string Defined::LUA_GAME_LOGIC_PATH = "Resources/Lua/gameLogic.lua";