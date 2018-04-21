#include "Player.h"



Player::Player()
{
	if (!mTexture.loadFromFile("Resources/Obstacle.png"))
	{
		//Error
	}
	mSprite.setTexture(mTexture);
	SetPos(0, 0);
	mSprite.setPosition(GetPos());
	mDirection = Defined::RIGHT;
}

Player::Player(int pXPos, int pYPos)
{
	if (!mTexture.loadFromFile("Resources/Player.png"))
	{
		//Error
	}
	mSprite.setTexture(mTexture);
	SetPos(pXPos * Defined::GRID_CELL_SIZE, pYPos * Defined::GRID_CELL_SIZE);
	mSprite.setPosition(GetPos());
	mDirection = Defined::RIGHT;
}


Player::~Player()
{
}

void Player::SetPosition(Vector2f pPosition)
{
	SetPos(pPosition.x, pPosition.y);
	mSprite.setPosition(Entity::GetPos());
}

Vector2f Player::GetPos()const
{
	return Entity::GetPos();
}

void Player::SetDirection(Defined::eDirection pDir)
{
	mDirection = pDir;
}

Defined::eDirection Player::GetDirection() const
{
	return mDirection;
}

void Player::Draw(RenderWindow & window)
{
	if (&window != nullptr)
	{
		window.draw(mSprite);
	}
}

void Player::Update(float dt)
{
	//if (mDirection == Defined::RIGHT)
	//{
	//	mSprite.setRotation(90);
	//}
	//else if (mDirection == Defined::LEFT)
	//{
	//	mSprite.setRotation(270);
	//}
	//else if (mDirection == Defined::UP)
	//{
	//	mSprite.setRotation(0);
	//}
	//else
	//{
	//	mSprite.setRotation(180);
	//}

	//if (Keyboard::isKeyPressed(Keyboard::D))
	//{
	//	SetPos(mPlayerSprite.getPosition().x + Defined::GRID_CELL_SIZE, mPlayerSprite.getPosition().y);
	//	mPlayerSprite.setPosition(GetPos());
	//}
	//if (Keyboard::isKeyPressed(Keyboard::S))
	//{
	//	SetPos(mPlayerSprite.getPosition().x, mPlayerSprite.getPosition().y + Defined::GRID_CELL_SIZE);
	//	mPlayerSprite.setPosition(GetPos());
	//}
	//if (Keyboard::isKeyPressed(Keyboard::A))
	//{
	//	SetPos(mPlayerSprite.getPosition().x - Defined::GRID_CELL_SIZE, mPlayerSprite.getPosition().y);
	//	mPlayerSprite.setPosition(GetPos());
	//}
	//if (Keyboard::isKeyPressed(Keyboard::W))
	//{
	//	SetPos(mPlayerSprite.getPosition().x, mPlayerSprite.getPosition().y - Defined::GRID_CELL_SIZE);
	//	mPlayerSprite.setPosition(GetPos());
	//}
}