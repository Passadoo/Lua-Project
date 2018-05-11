#include "Editor.h"

Editor::Editor()
{
	initObjects();
}

Editor::~Editor()
{
	if (mObjects)
	{
		delete[] mObjects;
	}

	if (mObjectTypes.size() != 0)
	{
		for (int i = 0; i < mObjectTypes.size(); i++)
		{
			delete mObjectTypes[i];
		}
	}
}

void Editor::Update(float dt, const sf::RenderWindow &window)
{
	mMousePos = sf::Mouse::getPosition(window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

	}
}

void Editor::Draw(sf::RenderWindow & window)
{
	if (&window != nullptr)
	{
		int position;
		for (int x = 0; x < Defined::WORLD_WIDTH; x++)
		{
			for (int y = 0; y < Defined::WORLD_HEIGHT; y++)
			{
				position = x + y * Defined::WORLD_WIDTH;
				if (mObjects[position]->objType != OBJECT_TYPES::NONE)
				{
					mObjects[position]->sprite.setPosition(x * Defined::GRID_CELL_SIZE, y * Defined::GRID_CELL_SIZE);
					window.draw(mObjects[position]->sprite);
				}
			}
		}
	}
}

void Editor::loadObjectTexture(Obj* obj, const std::string & objectPath)
{
	if (!obj->texture.loadFromFile(objectPath))
	{
		std::cout << "Texture from file [" << objectPath << "] could not be loaded" << std::endl;
	}
	obj->sprite.setTexture(obj->texture);
}

void Editor::createObjectTypes()
{
	for (int objType = OBJECT_TYPES::START; objType < OBJECT_TYPES::END; objType++)
	{
		Obj* obj = new Obj();
		obj->objType = (OBJECT_TYPES)objType;
		switch (objType)
		{
		case OBJECT_TYPES::OBSTACLE:
			loadObjectTexture(obj, Defined::OBSTACLE_PATH);
			break;
		case OBJECT_TYPES::DOOR:
			loadObjectTexture(obj, Defined::DOOR_PATH);
			break;
		case OBJECT_TYPES::ENEMY:
			loadObjectTexture(obj, Defined::ENEMY_PATH);
			break;
		default:
			break;
		}
		std::cout << "OnjectType: " << (OBJECT_TYPES)objType << ", " << NONE << std::endl;
		mObjectTypes.push_back(obj);
	}
}

void Editor::initObjects()
{
	createObjectTypes();

	int position = 0;
	mObjects = new Obj*[Defined::WORLD_WIDTH * Defined::WORLD_HEIGHT];
	for (int x = 0; x < Defined::WORLD_WIDTH; x++)
	{
		for (int y = 0; y < Defined::WORLD_HEIGHT; y++)
		{
			position = x + y * Defined::WORLD_WIDTH;
			mObjects[position] = mObjectTypes[NONE];
		}
	}
}
