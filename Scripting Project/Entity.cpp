#include "Entity.h"



Entity::Entity(float pXPos, float pYPos)
{
	mPosition = sf::Vector2f(pXPos, pYPos);
}


Entity::~Entity()
{
}