#include "Obstacle.h"



Obstacle::Obstacle()
{
	if (!mTexture.loadFromFile("Resources/Obstacle.png"))
	{
		//Error
	}
	mSprite.setTexture(mTexture);
	mSprite.setPosition(GetPos());
}

Obstacle::Obstacle(int pXPos, int pYPos)
{
	if (!mTexture.loadFromFile("Resources/Obstacle.png"))
	{
		//Error
	}
	mSprite.setTexture(mTexture);
	SetPos(pXPos * Defined::GRID_CELL_SIZE, pYPos * Defined::GRID_CELL_SIZE);
	mSprite.setPosition(GetPos());
}


Obstacle::~Obstacle()
{

}

void Obstacle::Draw(RenderWindow & window)
{
	if (&window != nullptr)
	{
		window.draw(mSprite);
	}
}

void Obstacle::Update(float dt)
{

}