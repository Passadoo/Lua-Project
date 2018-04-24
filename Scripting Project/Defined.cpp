#include "Defined.h"

//Window
unsigned int Defined::WINDOW_WIDTH = 800;
unsigned int Defined::WINDOW_HEIGHT = 600;

//Map
const string Defined::MAP_PATH = "Resources/Rooms/StartRoom.txt";

//Grid
int Defined::GRID_CELL_SIZE = 40; // 20 x 15 grid squares, each grid square 40 x 40 pixels large
int Defined::WORLD_WIDTH = 20; //20 grid cells wide
int Defined::WORLD_HEIGHT = 15; // 15 grid cells tall

//Time
const float Defined::BULLET_SPEED = 0.5;

//Enemies
const int Defined::ENEMY_HEALTH = 3;