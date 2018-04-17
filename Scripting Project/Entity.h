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

	virtual void Draw(RenderWindow &window) = 0;
	virtual void Update(float dt) = 0;

	void SetPos(const Vector2f &pos);
	void SetPos(float x, float y);
	Vector2f GetPos() const;
	float GetPosX() const;
	float GetPosY()const;

};

