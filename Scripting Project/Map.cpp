#include "Map.h"

Defined::ObjectTypes** Map::mObjectTypes = nullptr;
int Map::mNrOfEnemies = 0;
int Map::mNrOfObstacles = 0;
int Map::mNrOfDoors = 0;
vector<char> Map::mDirections;

void Map::fillGrid(const vector<string>& lines, const vector<char>& chars)
{
	char temp;
	Defined::ObjectTypes objType;

	for (int j = 0; j < Defined::WORLD_HEIGHT; j++)
	{
		for (int i = 0; i < Defined::WORLD_WIDTH; i++)
		{
			temp = lines.at(j).at(i);

			objType = Defined::AIR;
			Map::mObjectTypes[i][j] = objType;

			for (int k = 0; k < chars.size(); k++)
			{
				if (temp == chars.at(k))
				{
					if (temp == 'o')
					{
						objType = Defined::OBSTACLE;
						Map::mNrOfObstacles++;
					}
					else if(temp == 'e')
					{
						objType = Defined::ENEMY;
						Map::mNrOfEnemies++;
					}
					else if (temp != '.')
					{
						objType = Defined::DOOR;
						Map::mNrOfDoors++;
					}
					else if (temp != '.')
					{
						objType = Defined::PLAYER;
					}
					Map::mObjectTypes[i][j] = objType;
				}
			}
		}
	}
}

Map::Map()
{

}


Map::~Map()
{
	for (int i = 0; i < Defined::WORLD_WIDTH; i++)
	{
		delete[] Map::mObjectTypes[i];
	}
	delete[] Map::mObjectTypes;
}

bool Map::ReadMap(const string & path)
{
	std::ifstream ifs;
	char input;

	ifs.open(path);

	if (ifs.fail())
	{
		std::cout << "Cant open file: " << path << endl;
		return false;
	}

	vector<string> lines;
	vector<char> chars;
	string word;

	ifs >> word;

	if (word == "@Objects")
	{
		ifs >> word;

		while (word.size() == 1)
		{
			//chars.push_back(word[0]); //adding "p" to char list
			//ifs >> word;
			//mDirections.push_back(word[0]); //adding "l", "r", "u" or "d" to char list, indicating the direction the player is facing
			//ifs >> word;
			chars.push_back(word[0]); //adding "e" to the char list
			ifs >> word;
			mDirections.push_back(word[0]); //adding "l", "r", "u" or "d" to char list, indicating the direction the enemy is facing
			ifs >> word;
			chars.push_back(word[0]); //adding "o" to char list for obstacle placement
			ifs >> word;
			chars.push_back(word[0]); //adding "d" to char list for door placement
			ifs >> word;
			mDirections.push_back(word[0]); //adding "l", "r", "u" or "d" to char list, indicating the direction the door is facing
			ifs >> word; 

		}
		if (word == "@Map")
		{
			string line = "";
			getline(ifs, line); //skipped first line?
			while (!ifs.eof())
			{
				getline(ifs, line);
				lines.push_back(line);
			}
		}
	}

	if (lines.size() > 0)
	{
		Defined::WORLD_WIDTH = lines.at(0).size();
		Defined::WORLD_HEIGHT = lines.size();

		mObjectTypes = new Defined::ObjectTypes*[Defined::WORLD_WIDTH];
		for (int i = 0; i < Defined::WORLD_WIDTH; i++)
		{
			Map::mObjectTypes[i] = new Defined::ObjectTypes[Defined::WORLD_HEIGHT];
		}

		fillGrid(lines, chars);
	}

	ifs.close();

	return true;
}

void Map::setObjects(string filepath, Obstacle **& pObstacles, int & pNrOfObstacles, Enemy **& pEnemies, int & pNrOfEnemies,
	Door **& pDoors, int & pNrOfDoors)
{

	ReadMap(filepath);

	if (pObstacles != nullptr)
	{
		for (int i = 0; i < pNrOfObstacles; i++)
		{
			delete pObstacles[i];
		}
		delete[]pObstacles;
	}

	if (pEnemies != nullptr)
	{
		for (int i = 0; i < pNrOfEnemies; i++)
		{
			delete pEnemies[i];
		}
		delete[] pEnemies;
	}

	if (pDoors != nullptr)
	{
		for (int i = 0; i < pNrOfDoors; i++)
		{
			delete pDoors[i];
		}
		delete[] pDoors;
	}

	pNrOfObstacles = Map::mNrOfObstacles;
	pNrOfEnemies = Map::mNrOfEnemies;
	pNrOfDoors = Map::mNrOfDoors;

	pObstacles = new Obstacle*[Map::mNrOfObstacles];
	pEnemies = new Enemy*[Map::mNrOfEnemies];
	pDoors = new Door*[Map::mNrOfDoors];

	int tempObstacles = 0;
	int tempEnemies = 0;
	int tempDoors = 0;

	for (int i = 0; i < Defined::WORLD_WIDTH; i++)
	{
		for (int j = 0; j < Defined::WORLD_HEIGHT; j++)
		{
			if (Map::mObjectTypes[i][j] == Defined::OBSTACLE)
			{
				pObstacles[tempObstacles] = new Obstacle(i, j);
				tempObstacles++;
			}
			//if (Map::mObjectTypes[i][j] == Defined::PLAYER)
			//{
			//	pPlayer = new Player(i, j);
			//	if (mDirections[0] == 'l')
			//	{
			//		pPlayer->SetDirection(Defined::LEFT);
			//	}
			//	if (mDirections[0] == 'r')
			//	{
			//		pPlayer->SetDirection(Defined::RIGHT);
			//	}
			//	if (mDirections[0] == 'u')
			//	{
			//		pPlayer->SetDirection(Defined::UP);
			//	}
			//	if (mDirections[0] == 'd')
			//	{
			//		pPlayer->SetDirection(Defined::DOWN);
			//	}
			//}
			if (Map::mObjectTypes[i][j] == Defined::ENEMY)
			{
				pEnemies[tempEnemies] = new Enemy(i, j);
				if (mDirections[0] == 'l')
				{
					pEnemies[tempEnemies]->SetDirection(Defined::LEFT);
				}
				if (mDirections[0] == 'r')
				{
					pEnemies[tempEnemies]->SetDirection(Defined::RIGHT);
				}
				if (mDirections[0] == 'u')
				{
					pEnemies[tempEnemies]->SetDirection(Defined::UP);
				}
				if (mDirections[0] == 'd')
				{
					pEnemies[tempEnemies]->SetDirection(Defined::DOWN);
				}
				tempEnemies++;
			}
			if (Map::mObjectTypes[i][j] == Defined::DOOR)
			{
				pDoors[tempDoors] = new Door(i, j);
				
				if (mDirections[1] == 'l')
				{
					pDoors[tempDoors]->SetDirection(Defined::LEFT);
				}
				if (mDirections[1] == 'r')
				{
					pDoors[tempDoors]->SetDirection(Defined::RIGHT);
				}
				if (mDirections[1] == 'u')
				{
					pDoors[tempDoors]->SetDirection(Defined::UP);
				}
				if (mDirections[1] == 'd')
				{
					pDoors[tempDoors]->SetDirection(Defined::DOWN);
				}
				tempDoors++;
			}
		}
	}

	for (int i = 0; i < Defined::WORLD_WIDTH; i++)
	{
		delete[] Map::mObjectTypes[i];
	}
	delete[] Map::mObjectTypes;

}
