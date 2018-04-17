#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	RectangleShape mPlayerSprite;


public:
	Player();
	Player(int pXPos, int pYPos);
	~Player();
	
	void setPosition(Vector2f pPosition);

	void Draw(RenderWindow &window);
	void Update(float dt);
};

