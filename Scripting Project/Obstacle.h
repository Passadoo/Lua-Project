#pragma once

#include "Entity.h"

class Obstacle : public Entity
{
private:

	Texture mTexture;
	Sprite mSprite;

public:
	Obstacle();
	Obstacle(int pXPos, int pYPos);
	~Obstacle();

	void Draw(RenderWindow &window);
	void Update(float dt);
};

