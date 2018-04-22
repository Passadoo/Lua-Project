#include "Bullet.h"



Bullet::Bullet(int pXPos, int pYPos, Defined::eDirection pDir)
{
	mDirection = pDir;
	mTimeStep = Defined::BULLET_SPEED;

	if (!mTexture.loadFromFile("Resources/SmallBullet.png"))
	{
		std::cout << "Bullet texture could not be loaded" << std::endl;
	}
	mSprite.setTexture(mTexture);
	SetPos(pXPos, pYPos);
	mSprite.setPosition(GetPos());

}


Bullet::~Bullet()
{
}

Defined::eDirection Bullet::GetDirection() const
{
	return mDirection;
}

void Bullet::SetDirection(const Defined::eDirection pDir)
{
	mDirection = pDir;
}

Vector2f Bullet::GetBulletPos()
{
	return GetPos();
}

void Bullet::Draw(RenderWindow & window)
{
	if (&window != nullptr)
	{
		window.draw(mSprite);
	}
}

void Bullet::Update(float dt)
{
	mTimeStep -= dt;
	if (mTimeStep <= 0.0f)
	{
		mTimeStep = Defined::BULLET_SPEED;
		if (mDirection == Defined::UP)
		{
			SetPos(GetPos().x, GetPos().y - Defined::GRID_CELL_SIZE);
			mSprite.setPosition(Entity::GetPos());
		}
		else if (mDirection == Defined::DOWN)
		{
			SetPos(GetPos().x, GetPos().y + Defined::GRID_CELL_SIZE);
			mSprite.setPosition(Entity::GetPos());
		}
		else if (mDirection == Defined::RIGHT)
		{
			SetPos(GetPos().x + Defined::GRID_CELL_SIZE, GetPos().y);
			mSprite.setPosition(Entity::GetPos());
		}
		else
		{
			SetPos(GetPos().x - Defined::GRID_CELL_SIZE, GetPos().y);
			mSprite.setPosition(Entity::GetPos());
		}
	}
}
