#pragma once

#include "Entity.h"
#include <iostream>
#include "Bullet.h"
#include "ILuaMember.h"

class Player : public Entity, public ILuaMember
{
private:
	Texture mTexture;
	Sprite mSprite;

	Defined::eDirection mDirection;

public:
	Player();
	Player(int pXPos, int pYPos);
	~Player();
	

	void SetPosition(Vector2f pPosition);
	Vector2f GetPos()const;
	void SetDirection(/*Defined::eDirection*/int pDir);
	/*Defined::eDirection*/int GetDirection();

	void Draw(RenderWindow &window);
	void Update(float dt);


};

