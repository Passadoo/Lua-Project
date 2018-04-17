#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	RectangleShape mPlayerSprite;


public:
	Player();
	~Player();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

