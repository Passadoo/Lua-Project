#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Defined.h"
#include "MouseInput.h"
#include <fstream>

class Editor
{
public:
	Editor();
	~Editor();

	void Update(float dt);
	void Draw(sf::RenderWindow &window);
	void EnterText(const sf::Event & event);

private:
	enum OBJECT_TYPES { NONE, OBSTACLE, DOOR, ENEMY, END, START = NONE};
	struct Obj
	{
		OBJECT_TYPES objType;
		sf::Texture texture;
		sf::Sprite sprite;
	};
	Obj** mObjects;
	std::vector<Obj*> mObjectTypes;
	std::vector<Obj*> mEnemies;
	std::vector<Obj*> mObstacles;
	std::vector<Obj*> mDoors;

	// Editor things
	int mToCreate = OBJECT_TYPES::NONE;

	// Save level
	bool mSaveLevel = false;
	sf::String mPlayerInput;
	sf::Text mPlayerText;
	sf::Font mFont;

private:
	void loadObjectTexture(Obj* obj, const std::string & objectPath);
	void createObjectTypes();
	void initObjects();
	void processInput();
	void createObject(OBJECT_TYPES objectType);
	void addToList(OBJECT_TYPES objectType);

	// Save
	bool saveLevel(const std::string &name);
	void addToRoomInfo(const std::string &name, const std::string &doorsNr);
	
	// Graphics
	void drawSelectionBox(sf::RenderWindow &window, float x, float y, float border);

	// Utilities
	sf::Vector2i mouseToWorldCoord();
};