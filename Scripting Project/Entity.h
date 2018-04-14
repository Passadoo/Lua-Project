#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Entity
{
private:
	Vector2f mPosition;

public:
	Entity(float pXPos, float pYPos);
	~Entity();

	virtual void draw(RenderWindow &window) = 0;
	virtual void update(float dt, Entity** other = nullptr, int size = 0) = 0;

	void setPos(const Vector2f &pos);
	void setPos(float x, float y);
	Vector2f getPos() const;
	float getPosX() const;
	float getPosY()const;

};

