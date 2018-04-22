#include "Door.h"



Door::Door()
{
	if (!mTexture.loadFromFile("Resources/Door.png"))
	{

	}
	mSprite.setTexture(mTexture);
	SetPos(0, 0);
	mSprite.setPosition(GetPos());
	mDirection = Defined::RIGHT;
}

Door::Door(int pPosX, int pPosY)
{
	if (!mTexture.loadFromFile("Resources/Door.png"))
	{
		//Error
	}
	mSprite.setTexture(mTexture);
	SetPos(pPosX * Defined::GRID_CELL_SIZE, pPosY * Defined::GRID_CELL_SIZE);
	mSprite.setPosition(GetPos());
	mDirection = Defined::RIGHT;
}


Door::~Door()
{

}

void Door::SetDirection(Defined::eDirection pDir)
{
	mDirection = pDir;
}

Defined::eDirection Door::GetDirection() const
{
	return mDirection;
}

void Door::Draw(RenderWindow & window)
{
	window.draw(mSprite);
}

void Door::Update(float dt)
{

}
