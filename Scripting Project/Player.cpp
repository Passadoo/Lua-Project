#include "Player.h"



Player::Player()
{
	mPlayerSprite = RectangleShape(Vector2f(50, 50));
	mPlayerSprite.setFillColor(Color::Blue);
	mPlayerSprite.setPosition(4, 4);
}


Player::~Player()
{
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
