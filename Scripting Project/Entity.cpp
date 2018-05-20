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
	this->SetPos(pPosition.x, pPosition.y);
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

float Entity::GetPosX()
{
	return this->mPosition.x;
}

float Entity::GetPosY()
{
	return this->mPosition.y;
}