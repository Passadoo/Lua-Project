#pragma once
#include "Entity.h"
#include "ILuaMember.h"

class Enemy : public Entity, public ILuaMember
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

	void TestLuaFunction1();
	void TestLuaFunction2(int i);
	int TestLuaFunction3(int i);
	void TestLuaFunction4(int i);
	void TestLuaFunction5(int i, int j);
	bool TestLuaFunction6(int i, int j);

	int mI = 0;
};

