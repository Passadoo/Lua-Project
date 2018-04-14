#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
private:
	sf::Vector2f mPosition;

public:
	Entity(float pXPos, float pYPos);
	~Entity();


};

