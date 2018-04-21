#include "Map.h"



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
			mObjectTypes[i][j] = objType;

			for (int k = 0; k < chars.size(); k++)
			{
				if (temp == chars.at(k))
				{
					if (temp == 'o')
					{
						objType = Defined::OBSTACLE;
						mNrOfObstacles++;
					}
					else if(temp == 'e')
					{
						objType = Defined::ENEMY;
						mNrOfEnemies++;
					}
					else if (temp != '.')
					{
						objType = Defined::PLAYER;
					}
					mObjectTypes[i][j] = objType;
				}
			}
		}
	}
}

Map::Map()
{
	mObjectTypes = nullptr;
	mNrOfEnemies = 0;
	mNrOfObstacles = 0;
}


Map::~Map()
{
	for (int i = 0; i < Defined::WORLD_WIDTH; i++)
	{
		delete[] mObjectTypes[i];
	}
	delete[] mObjectTypes;
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
			chars.push_back(word[0]); //adding "p" to char list
			ifs >> word;
			mDirections.push_back(word[0]); //adding "l", "r", "u" or "d" to char list, indicating the direction the player is facing
			ifs >> word;
			chars.push_back(word[0]); //adding "e" to the char list
			ifs >> word;
			mDirections.push_back(word[0]); //adding "l", "r", "u" or "d" to char list, indicating the direction the enemy is facing
			ifs >> word;
			chars.push_back(word[0]); //adding "o" to char list for obstacle placement
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
			this->mObjectTypes[i] = new Defined::ObjectTypes[Defined::WORLD_HEIGHT];
		}

		fillGrid(lines, chars);
	}

	ifs.close();

	return true;


}

void Map::setObjects(Player* & pPlayer, Obstacle **& pObstacles, int & pNrOfObstacles, Enemy **& pEnemies, int & pNrOfEnemies)
{
	if (pPlayer != nullptr)
	{
		delete pPlayer;
	}

	if (pObstacles != nullptr)
	{
		for (int i = 0; i < pNrOfObstacles; i++)
		{
			delete pObstacles[i];
		}
		delete[] pObstacles;
	}

	if (pEnemies != nullptr)
	{
		for (int i = 0; i < pNrOfEnemies; i++)
		{
			delete pEnemies[i];
		}
		delete[] pEnemies;
	}

	pNrOfObstacles = mNrOfObstacles;
	pNrOfEnemies = mNrOfEnemies;

	pObstacles = new Obstacle*[mNrOfObstacles];
	pEnemies = new Enemy*[mNrOfEnemies];
	int tempObstacles = 0;
	int tempEnemies = 0;

	for (int i = 0; i < Defined::WORLD_WIDTH; i++)
	{
		for (int j = 0; j < Defined::WORLD_HEIGHT; j++)
		{
			if (mObjectTypes[i][j] == Defined::OBSTACLE)
			{
				pObstacles[tempObstacles] = new Obstacle(i, j);
				tempObstacles++;
			}
			if (mObjectTypes[i][j] == Defined::PLAYER)
			{
				pPlayer = new Player(i, j);
				if (mDirections[0] == 'l')
				{
					pPlayer->SetDirection(Defined::LEFT);
				}
				if (mDirections[0] == 'r')
				{
					pPlayer->SetDirection(Defined::RIGHT);
				}
				if (mDirections[0] == 'u')
				{
					pPlayer->SetDirection(Defined::UP);
				}
				if (mDirections[0] == 'd')
				{
					pPlayer->SetDirection(Defined::DOWN);
				}
				
			}
			if (mObjectTypes[i][j] == Defined::ENEMY)
			{
				pEnemies[tempEnemies] = new Enemy(i, j);
				if (mDirections[1] == 'l')
				{
					pEnemies[tempEnemies]->SetDirection(Defined::LEFT);
				}
				if (mDirections[1] == 'r')
				{
					pEnemies[tempEnemies]->SetDirection(Defined::RIGHT);
				}
				if (mDirections[1] == 'u')
				{
					pEnemies[tempEnemies]->SetDirection(Defined::UP);
				}
				if (mDirections[1] == 'd')
				{
					pEnemies[tempEnemies]->SetDirection(Defined::DOWN);
				}

				tempEnemies++;
			}
		}
	}


}
