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
		SetPos(mPlayerSprite.getPosition().x + Defined::GRID_CELL_SIZE, mPlayerSprite.getPosition().y);
		mPlayerSprite.setPosition(GetPos());
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		SetPos(mPlayerSprite.getPosition().x, mPlayerSprite.getPosition().y + Defined::GRID_CELL_SIZE);
		mPlayerSprite.setPosition(GetPos());
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		SetPos(mPlayerSprite.getPosition().x - Defined::GRID_CELL_SIZE, mPlayerSprite.getPosition().y);
		mPlayerSprite.setPosition(GetPos());
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		SetPos(mPlayerSprite.getPosition().x, mPlayerSprite.getPosition().y - Defined::GRID_CELL_SIZE);
		mPlayerSprite.setPosition(GetPos());
	}
}
