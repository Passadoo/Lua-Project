#include "Entity.h"



Entity::Entity(int pXPos, int pYPos)
{
	mPosition = Vector2f(pXPos, pYPos);
}


Entity::~Entity()
{

}

void Entity::SetPos(const Vector2f & pPosition) //Broken?
{
	this->SetPos(mPosition.x, mPosition.y);
}

void Entity::SetPos(int x, int y)
{
	this->mPosition.x = x;
	this->mPosition.y = y;
}

Vector2f Entity::GetPos() const
{
	return this->mPosition;
}

float Entity::GetPosX() const
{
	return this->mPosition.x;
}

float Entity::GetPosY() const
{
	return this->mPosition.y;
}