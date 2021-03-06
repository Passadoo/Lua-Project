#include "Editor.h"

Editor::Editor()
{
	initLuaManager();

	initObjects();
	mTextField.setPosition(Defined::WINDOW_WIDTH / 2.0f, Defined::WINDOW_HEIGHT / 2.0f);

	if (!mFont.loadFromFile("Resources/Gabriola.ttf"))
	{
		std::cout << "Could not load the font" << std::endl;
	}
	mTextField.setFont(mFont);

	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		mKeys[i] = false;
	}
}

Editor::~Editor()
{
	LuaManager::CloseLuaManager();

	if (mObjects)
	{
		delete[] mObjects;
	}

	if (mObjectTypes.size() != 0)
	{
		for (int i = 0; i < (int)mObjectTypes.size(); i++)
		{
			delete mObjectTypes[i];
		}
	}
}

void Editor::Update(float dt)
{
	if (mText.size() != 0)
		mTextField.setString(mText);
}

void Editor::ProcessInputs()
{
	processInput();
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
				if (mObjects[position]->objType != NONE)
				{
					mObjects[position]->sprite.setPosition((float)(x * Defined::GRID_CELL_SIZE), (float)(y * Defined::GRID_CELL_SIZE));
					window.draw(mObjects[position]->sprite);
				}
			}
		}

		// Draw toCreate
		float border = 10;
		drawSelectionBox(window, 0, 0, border);

		int ret = LuaManager::CallLuaFunc<int>("GetToCreate");
		mObjectTypes[ret]->sprite.setPosition(border, border);
		window.draw(mObjectTypes[ret]->sprite);

		// Draw textbox for saveing the level
		if (mSaveLevel)
		{
			float h = Defined::WINDOW_HEIGHT / 6.0f;
			float w = Defined::WINDOW_WIDTH / 3.0f;
			sf::RectangleShape box(sf::Vector2f(w, h));
			box.setPosition(Defined::WINDOW_WIDTH / 2.0f, Defined::WINDOW_HEIGHT / 2.0f);
			box.setOrigin(w / 2.0f, h / 4.0f);
			sf::Color color = sf::Color::Green;
			color.a = 50;
			box.setFillColor(color);
			box.setOutlineColor(sf::Color::Black);
			box.setOutlineThickness(border);
			window.draw(box);
			float width = mTextField.getLocalBounds().width;
			mTextField.setOrigin(width / 2.0f, 0);
			window.draw(mTextField);
		}
	}
}

void Editor::EnterText()
{
	if (mSaveLevel)
	{
		bool toLower = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
			toLower = true;

		for (int key = sf::Keyboard::Key::A; key < sf::Keyboard::Key::KeyCount; key++)
		{
			if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key) && !mKeys[key])
			{
				mKeys[key] = true;
				char ch = MKeyboard::fromKeyToChar((sf::Keyboard::Key)key);
				if (ch != '?')
				{
					if (key >= sf::Keyboard::Key::A && key <= sf::Keyboard::Key::Z && !toLower)
					{
						ch = std::tolower(ch);
					}
					mText.push_back(ch);
				}
				else if ((sf::Keyboard::Key)key == sf::Keyboard::BackSpace)
				{
					if (mText.size() > 0)
						mText.pop_back();
					mTextField.setString(mText);
				}
			}
			else
			{
				mKeys[key] = false;
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
	for (int objType = START; objType < END; objType++)
	{
		Obj* obj = new Obj();
		obj->objType = (OBJECT_TYPES)objType;
		switch (objType)
		{
		case OBSTACLE:
			loadObjectTexture(obj, Defined::OBSTACLE_PATH);
			break;
		case DOOR:
			loadObjectTexture(obj, Defined::DOOR_PATH);
			break;
		case ENEMY:
			loadObjectTexture(obj, Defined::ENEMY_PATH);
			break;
		default:
			break;
		}
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
			if ((x == 0 || x == Defined::WORLD_WIDTH - 1) || (y == 0 || y == Defined::WORLD_HEIGHT - 1))
				mObjects[position] = mObjectTypes[OBSTACLE];
			else
				mObjects[position] = mObjectTypes[NONE];

			addToList(mObjects[position]->objType);
		}
	}
}

void Editor::processInput()
{
	if (!mSaveLevel)
	{
		if (MouseInput::wheelUp())
		{
			LuaManager::CallLuaFunc<void>("decrementToCreate", (int)START, (int)END);
		}
		if (MouseInput::wheelDown())
		{
			LuaManager::CallLuaFunc<void>("incrementToCreate", (int)START, (int)END);
		}

		if (MouseInput::isPressed(sf::Mouse::Left))
		{
			int ret = LuaManager::CallLuaFunc<int>("GetToCreate");
			if (ret != NONE)
				createObject((OBJECT_TYPES)ret);
		}
		if (MouseInput::isPressed(sf::Mouse::Right))
		{
			createObject(NONE);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			mSaveLevel = true;
			mTextField.setString("Write the name of the file");
			float width = mTextField.getLocalBounds().width;
			mTextField.setOrigin(width / 2.0f, 0);
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		mSaveLevel = false;
		if (saveLevel(mText))
		{
			mText = "";
			mTextField.setString("");
			std::cout << "Saved level" << std::endl;
		}
	}
}

void Editor::createObject(OBJECT_TYPES objectType)
{
	sf::Vector2i pos = mouseToWorldCoord();
	addToList(objectType);
	mObjects[pos.x + pos.y * Defined::WORLD_WIDTH] = mObjectTypes[objectType];
}

void Editor::addToList(OBJECT_TYPES objectType)
{
	switch (objectType)
	{
	case OBSTACLE:
		mObstacles.push_back(mObjectTypes[objectType]);
		break;
	case DOOR:
		mDoors.push_back(mObjectTypes[objectType]);
		break;
	case ENEMY:
		mEnemies.push_back(mObjectTypes[objectType]);
		break;
	default:
		break;
	}
}

bool Editor::saveLevel(const std::string & filename)
{
	bool canSave = false;
	int position;
	std::string doorsNr = "0000";
	for (int x = 0; x < Defined::WORLD_WIDTH; x++)
	{
		for (int y = 0; y < Defined::WORLD_HEIGHT; y++)
		{
			position = x + y * Defined::WORLD_WIDTH;
			if ((x == 0 || x == Defined::WORLD_WIDTH - 1) || (y == 0 || y == Defined::WORLD_HEIGHT - 1))
			{
				if (mObjects[position]->objType == DOOR)
				{
					canSave = true;
					if (y == 0)
						doorsNr.at(0) = '1';
					if (x == Defined::WORLD_WIDTH - 1)
						doorsNr.at(1) = '1';
					if (y == Defined::WORLD_HEIGHT - 1)
						doorsNr.at(2) = '1';
					if (x == 0)
						doorsNr.at(3) = '1';
				}
			}
		}
	}

	if (canSave)
	{
		ofstream ofs;
		ofs.open(Defined::ROOMS_PATH + filename);

		ofs << "@Objects\n";
		if (mEnemies.size() != 0)
		{
			ofs << "e r\n";
		}
		if (mObstacles.size() != 0)
		{
			ofs << "o\n";
		}
		if (mDoors.size() != 0)
		{
			ofs << "d d\n";
		}
		ofs << "@Map\n";
		int position;
		for (int y = 0; y < Defined::WORLD_HEIGHT; y++)
		{
			for (int x = 0; x < Defined::WORLD_WIDTH; x++)
			{
				position = x + y * Defined::WORLD_WIDTH;
				if (mObjects[position]->objType == ENEMY)
				{
					ofs << "e";
				}
				else if (mObjects[position]->objType == OBSTACLE)
				{
					ofs << "o";
				}
				else if (mObjects[position]->objType == DOOR)
				{
					ofs << "d";
				}
				else
				{
					ofs << ".";
				}
			}
			ofs << "\n";
		}
		ofs.close();

		addToRoomInfo(filename, doorsNr);
	}
	return canSave;
}

void Editor::addToRoomInfo(const std::string & name, const std::string & doorsNr)
{
	bool exists = false;
	std::string file = "";
	ifstream ifs;
	ifs.open(Defined::ROOM_INFO_PATH);
	std::string word;
	while (!ifs.eof())
	{
		std::getline(ifs, word);
		if (word.substr(0, name.size()) == name)
		{
			std::cout << "name: " << word.substr(0, name.size()) << ", " << name << std::endl;
			exists = true;
			word = "";
		}
		else
			file += word + "\n";
	}
	ifs.close();

	if (!exists)
	{
		ofstream ofs;
		ofs.open(Defined::ROOM_INFO_PATH);

		ofs << file;
		ofs << name;
		ofs << " " << doorsNr;

		ofs.close();
	}
	else
	{
		std::cout << "The filename already exists" << std::endl;
	}
}

void Editor::drawSelectionBox(sf::RenderWindow &window, float x, float y, float border)
{
	float size = (float)Defined::GRID_CELL_SIZE + 2.0f * border;
	sf::RectangleShape shape(sf::Vector2f(size, size));
	sf::Color color = sf::Color::Blue;
	color.a = 50;
	shape.setFillColor(color);
	shape.setPosition(0.0f, 0.0f);
	shape.setOutlineThickness(-border / 2.0f);
	shape.setOutlineColor(sf::Color::Cyan);
	window.draw(shape);
}

sf::Vector2i Editor::mouseToWorldCoord()
{
	sf::Vector2i pos;
	pos.x = (int)((float)(MouseInput::GetX() / (float)Defined::WINDOW_WIDTH) * Defined::WORLD_WIDTH);
	pos.y = (int)((float)(MouseInput::GetY() / (float)Defined::WINDOW_HEIGHT) * Defined::WORLD_HEIGHT);
	return pos;
}

void Editor::initLuaManager()
{
	LuaManager::InitLuaManager();

	LuaManager::LoadScript(Defined::LUA_EDITOR_PATH);
}
