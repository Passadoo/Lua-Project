#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
	Texture mTexture;
	Sprite mSprite;
	int mCurrentHealth;

	Defined::eDirection mDirection;

	float mTime;
public:
	Enemy();
	Enemy(float pPosX, float pPosY);
	~Enemy();

	void SetPosition(float x, float y);
	Vector2f GetPos()const;
	void SetDirection(int pDir);
	Defined::eDirection GetDirection()const;
	void TakeDamage();
	int GetHealth()const;

	void Draw(RenderWindow &window);
	void Update(float dt);

	float GetTime();
	void SetTime(float pTime);
};

