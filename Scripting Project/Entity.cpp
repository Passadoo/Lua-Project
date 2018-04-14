#include "Entity.h"



Entity::Entity(float pXPos, float pYPos)
{
	mPosition = Vector2f(pXPos, pYPos);
	//Test comment
}


Entity::~Entity()
{

}

void Entity::SetPos(const Vector2f & pPosition)
{
	this->SetPos(mPosition.x, mPosition.y);
}

void Entity::SetPos(float x, float y)
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