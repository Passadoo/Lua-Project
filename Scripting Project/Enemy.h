#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
	Texture mTexture;
	Sprite mSprite;
	int mCurrentHealth;

	Defined::eDirection mDirection;

public:
	Enemy();
	Enemy(float pPosX, float pPosY);
	~Enemy();

	void SetPosition(Vector2f pPosition);
	Vector2f GetPos()const;
	void SetDirection(Defined::eDirection pDir);
	Defined::eDirection GetDirection()const;
	void TakeDamage();
	int GetHealth()const;

	void Draw(RenderWindow &window);
	void Update(float dt);
};

