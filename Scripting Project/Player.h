#pragma once

#include "Entity.h"
#include <iostream>
#include "Bullet.h"

class Player : public Entity
{
private:
	Texture mTexture;
	Sprite mSprite;

	Defined::eDirection mDirection;

public:
	Player();
	Player(int pXPos, int pYPos);
	~Player();

	void SetPosition(float x, float y);
	Vector2f GetPos()const;
	void SetDirection(/*Defined::eDirection*/int pDir);
	/*Defined::eDirection*/int GetDirection();

	void Draw(RenderWindow &window);
	void Update(float dt);

};

