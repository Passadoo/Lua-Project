#pragma once

#include "Entity.h"
#include <iostream>

class Player : public Entity
{


public:
	Player();
	Player(int pXPos, int pYPos);
	~Player();
	
	enum eDirection { UP = 0, DOWN, LEFT, RIGHT };

	void SetPosition(Vector2f pPosition);
	Vector2f GetPos()const;
	void SetDirection(eDirection pDir);
	eDirection GetDirection()const;

	void Draw(RenderWindow &window);
	void Update(float dt);

private:
	RectangleShape mPlayerSprite;


	eDirection mDirection;
};

