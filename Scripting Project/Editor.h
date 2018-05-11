#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Defined.h"

class Editor
{
public:
	Editor();
	~Editor();

	void Update(float dt, const sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);

private:
	sf::Vector2i mMousePos;
	enum OBJECT_TYPES { NONE, OBSTACLE, DOOR, ENEMY, END, START = NONE};
	struct Obj
	{
		OBJECT_TYPES objType;
		sf::Texture texture;
		sf::Sprite sprite;
	};
	Obj** mObjects;
	std::vector<Obj*> mObjectTypes;

private:
	void loadObjectTexture(Obj* obj, const std::string & objectPath);
	void createObjectTypes();
	void initObjects();
};