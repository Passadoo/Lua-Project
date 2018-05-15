#include "Door.h"



Door::Door()
{
	if (!mTexture.loadFromFile(Defined::DOOR_PATH))
	{

	}
	mSprite.setTexture(mTexture);
	SetPos(0, 0);
	mSprite.setPosition(GetPos());
	mDirection = Defined::RIGHT;
}

Door::Door(int pPosX, int pPosY)
{
	if (!mTexture.loadFromFile(Defined::DOOR_PATH))
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

void Door::Update(float dt)
{

}
