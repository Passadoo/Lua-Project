#include "Player.h"



Player::Player()
{
	if (!mTexture.loadFromFile("Resources/Player.png"))
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

void Player::Update(float dt)
{

}