#pragma once
#include <SFML/Graphics.hpp>
#include "Defined.h"
#include "ILuaMember.h"

using namespace sf;

class Entity : public ILuaMember
{
private:
	Vector2f mPosition;

public:
	Entity(int pXPos = 0, int pYPos = 0);
	~Entity();

	virtual void Draw(RenderWindow &window) = 0;
	virtual void Update(float dt) = 0;

	void SetPos(const Vector2f &pos);
	void SetPos(int x, int y);
	Vector2f GetPos() const;
	float GetPosX();
	float GetPosY();

};

