#include "Enemy.h"

Enemy::Enemy()
{
	if (!mTexture.loadFromFile(Defined::ENEMY_PATH))
	{
		//Error
	}
	mSprite.setTexture(mTexture);
	SetPos(0, 0);
	mSprite.setPosition(GetPos());
	mDirection = Defined::RIGHT;
	mCurrentHealth = Defined::ENEMY_HEALTH;
}

Enemy::Enemy(float pPosX, float pPosY)
{
	if (!mTexture.loadFromFile(Defined::ENEMY_PATH))
	{
		//Error
	}
	mSprite.setTexture(mTexture);
	SetPos(pPosX * Defined::GRID_CELL_SIZE, pPosY * Defined::GRID_CELL_SIZE);
	mSprite.setPosition(GetPos());
	mDirection = Defined::RIGHT;
	mCurrentHealth = Defined::ENEMY_HEALTH;
}

Enemy::~Enemy()
{
}

void Enemy::SetPosition(Vector2f pPosition)
{
	SetPos(pPosition.x, pPosition.y);
	mSprite.setPosition(Entity::GetPos());
}

Vector2f Enemy::GetPos() const
{
	return Entity::GetPos();
}

void Enemy::SetDirection(Defined::eDirection pDir)
{
	mDirection = pDir;
}

Defined::eDirection Enemy::GetDirection() const
{
	return mDirection;
}

void Enemy::TakeDamage()
{
	mCurrentHealth--;
}

int Enemy::GetHealth() const
{
	return mCurrentHealth;
}

void Enemy::Draw(RenderWindow & window)
{
	Transform t;

	if (mDirection == Defined::RIGHT)
	{
		t.rotate(90, GetPos().x + (Defined::GRID_CELL_SIZE / 2), GetPos().y + (Defined::GRID_CELL_SIZE / 2));
		window.draw(mSprite, t);
	}
	else if (mDirection == Defined::LEFT)
	{
		t.rotate(270, GetPos().x + (Defined::GRID_CELL_SIZE / 2), GetPos().y + (Defined::GRID_CELL_SIZE / 2));
		window.draw(mSprite, t);
	}
	else if (mDirection == Defined::UP)
	{
		t.rotate(0, GetPos().x + (Defined::GRID_CELL_SIZE / 2), GetPos().y + (Defined::GRID_CELL_SIZE / 2));
		window.draw(mSprite, t);
	}
	else
	{
		t.rotate(180, GetPos().x + (Defined::GRID_CELL_SIZE / 2), GetPos().y + (Defined::GRID_CELL_SIZE / 2));
		window.draw(mSprite, t);
	}
}

void Enemy::Update(float dt)
{

}

void Enemy::TestLuaFunction1()
{
	std::cout << "Called " << __func__ << std::endl;
}

void Enemy::TestLuaFunction2(int i)
{
	std::cout << "Called " << __func__ << ", Return: " << i << std::endl;
}
