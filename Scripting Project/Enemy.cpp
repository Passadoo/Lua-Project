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
	mTime = 0.0f;
}

Enemy::Enemy(float pPosX, float pPosY)
{
	if (!mTexture.loadFromFile(Defined::ENEMY_PATH))
	{
		//Error
	}
	mSprite.setTexture(mTexture);
	SetPos((int)(pPosX * Defined::GRID_CELL_SIZE), (int)(pPosY * Defined::GRID_CELL_SIZE));
	mSprite.setPosition(GetPos());
	mDirection = Defined::RIGHT;
	mCurrentHealth = Defined::ENEMY_HEALTH;
	mTime = 0.0f;
}

Enemy::~Enemy()
{
}

void Enemy::SetPosition(float x, float y)
{
	SetPos((int)x, (int)y);
	mSprite.setPosition(Entity::GetPos());
}

Vector2f Enemy::GetPos() const
{
	return Entity::GetPos();
}

void Enemy::SetDirection(int pDir)
{
	mDirection = (Defined::eDirection)pDir;
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

float Enemy::GetTime()
{
	return mTime;
}

void Enemy::SetTime(float pTime)
{
	mTime = pTime;
}