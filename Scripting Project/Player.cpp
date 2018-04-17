#include "Player.h"



Player::Player()
{
	mPlayerSprite = RectangleShape(Vector2f(Defined::GRID_CELL_SIZE, Defined::GRID_CELL_SIZE));
	mPlayerSprite.setFillColor(Color::Blue);
	mPlayerSprite.setPosition(GetPos());
}

Player::Player(int pXPos, int pYPos)
{
	mPlayerSprite = RectangleShape(Vector2f(Defined::GRID_CELL_SIZE, Defined::GRID_CELL_SIZE));
	mPlayerSprite.setFillColor(Color::Blue);
	SetPos(pXPos * Defined::GRID_CELL_SIZE, pYPos * Defined::GRID_CELL_SIZE);
	mPlayerSprite.setPosition(GetPos());
}


Player::~Player()
{
}

void Player::setPosition(Vector2f pPosition)
{
	SetPos(pPosition);
	mPlayerSprite.setPosition(GetPos());
}

void Player::Draw(RenderWindow & window)
{
	if (&window != nullptr)
	{
		window.draw(mPlayerSprite);
	}
}

void Player::Update(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		mPlayerSprite.setPosition(mPlayerSprite.getPosition().x + 1, mPlayerSprite.getPosition().y);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		mPlayerSprite.setPosition(mPlayerSprite.getPosition().x, mPlayerSprite.getPosition().y + 1);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		mPlayerSprite.setPosition(mPlayerSprite.getPosition().x - 1, mPlayerSprite.getPosition().y);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		mPlayerSprite.setPosition(mPlayerSprite.getPosition().x, mPlayerSprite.getPosition().y - 1);
	}
}
