#include "Entity.h"



Entity::Entity(float pXPos, float pYPos)
{
	mPosition = Vector2f(pXPos, pYPos);
	//Test comment
}


Entity::~Entity()
{

}

void Entity::setPos(const Vector2f & pPosition)
{
	this->setPos(mPosition.x, mPosition.y);
}

void Entity::setPos(float x, float y)
{
	this->mPosition.x = x;
	this->mPosition.y = y;
}

Vector2f Entity::getPos() const
{
	return this->mPosition;
}

float Entity::getPosX() const
{
	return this->mPosition.x;
}

float Entity::getPosY() const
{
	return this->mPosition.y;
}