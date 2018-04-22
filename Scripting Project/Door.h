#pragma once

#include "Entity.h"

class Door : public Entity
{
private:
	Sprite mSprite;
	Texture mTexture;
	Defined::eDirection mDirection;

public:
	Door();
	Door(int pPosX, int pPosY);
	~Door();

	void SetDirection(Defined::eDirection pDir);
	Defined::eDirection GetDirection()const;

	void Draw(RenderWindow &window);
	void Update(float dt);
};

