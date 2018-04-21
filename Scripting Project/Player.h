#pragma once

#include "Entity.h"
#include <iostream>
#include "Bullet.h"

class Player : public Entity
{


public:
	Player();
	Player(int pXPos, int pYPos);
	~Player();
	

	void SetPosition(Vector2f pPosition);
	Vector2f GetPos()const;
	void SetDirection(Defined::eDirection pDir);
	Defined::eDirection GetDirection()const;

	void Draw(RenderWindow &window);
	void Update(float dt);

private:
	Texture mTexture;
	Sprite mSprite;

	Defined::eDirection mDirection;
};

