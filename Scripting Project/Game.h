#pragma once

#include "Player.h"
#include "Obstacle.h"

class Game
{
private:
	std::vector<Obstacle*> mObstacles;
	Player* mPlayer;

public:
	Game();
	~Game();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

