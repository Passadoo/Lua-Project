#pragma once
#include "Entity.h"
#include <iostream>

using namespace sf;

class Bullet : public Entity
{
private:
	Defined::eDirection mDirection;

	Sprite mSprite;
	Texture mTexture;

	float mTimeStep;

public:
	Bullet(int pXPos, int pYPos, Defined::eDirection pDir);
	~Bullet();

	Defined::eDirection GetDirection()const;
	void SetDirection(const Defined::eDirection pDir);
	Vector2f GetBulletPos();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

