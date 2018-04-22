#include "Game.h"

void Game::playerUpdate(float dt)
{
	bool moveInit = false;
	Vector2f nextPos;

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		if (mPlayer->GetDirection() == Defined::RIGHT)
		{
			nextPos = Vector2f(mPlayer->GetPos().x + Defined::GRID_CELL_SIZE, mPlayer->GetPos().y);
			moveInit = true;
		}
		else 
		{
			mPlayer->SetDirection(Defined::RIGHT);
		}

	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		if (mPlayer->GetDirection() == Defined::DOWN)
		{
			nextPos = Vector2f(mPlayer->GetPos().x, mPlayer->GetPos().y + Defined::GRID_CELL_SIZE);
			moveInit = true;
		}
		else
		{
			mPlayer->SetDirection(Defined::DOWN);
		}

	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		if (mPlayer->GetDirection() == Defined::LEFT)
		{
			nextPos = Vector2f(mPlayer->GetPos().x - Defined::GRID_CELL_SIZE, mPlayer->GetPos().y);
			moveInit = true;
		}
		else
		{
			mPlayer->SetDirection(Defined::LEFT);
		}

	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (mPlayer->GetDirection() == Defined::UP)
		{
			nextPos = Vector2f(mPlayer->GetPos().x, mPlayer->GetPos().y - Defined::GRID_CELL_SIZE);
			moveInit = true;
		}
		else
		{
			mPlayer->SetDirection(Defined::UP);
		}

	}

	if (moveInit)
	{
		bool canMove = true;

		for (int i = 0; i < mNrOfObstacles; i++)
		{
			if (mObstacles[i]->GetPos().x == nextPos.x && mObstacles[i]->GetPos().y == nextPos.y)
			{
				canMove = false;
			}
		}

		if (canMove)
		{
			mPlayer->SetPosition(nextPos);
		}
	}


	mPlayer->Update(dt);
}

void Game::bulletUpdate(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (mNrOfBullets < 5)
		{
			mBullets[mNrOfBullets] = new Bullet(mPlayer->GetPos().x, mPlayer->GetPos().y, mPlayer->GetDirection());
			mNrOfBullets++;
		}
	}

	Vector2f nextPos;
	Defined::eDirection bulletDirection;

	for (int i = 0; i < mNrOfBullets; i++)
	{
		bulletDirection = mBullets[i]->GetDirection();
		if (bulletDirection == Defined::UP)
		{
			nextPos = Vector2f(mBullets[i]->GetPos().x, mBullets[i]->GetPos().y - Defined::GRID_CELL_SIZE);
		}
		else if (bulletDirection == Defined::RIGHT)
		{
			nextPos = Vector2f(mBullets[i]->GetPos().x + Defined::GRID_CELL_SIZE, mBullets[i]->GetPos().y);
		}
		else if (bulletDirection == Defined::LEFT)
		{
			nextPos = Vector2f(mBullets[i]->GetPos().x - Defined::GRID_CELL_SIZE, mBullets[i]->GetPos().y);
		}
		else
		{
			nextPos = Vector2f(mBullets[i]->GetPos().x, mBullets[i]->GetPos().y + Defined::GRID_CELL_SIZE);
		}

		bool noWall = true;

		for (int i = 0; i < mNrOfObstacles; i++)
		{
			if (mObstacles[i]->GetPos().x == nextPos.x && mObstacles[i]->GetPos().y == nextPos.y)
			{
				noWall = false;
			}
		}

		bool noEnemy = true;
		for (int i = 0; i < mNrOfEnemies; i++)
		{
			if (mEnemies[i]->GetPos().x == nextPos.x && mEnemies[i]->GetPos().y == nextPos.y)
			{
				noEnemy = false;
				mEnemies[i]->TakeDamage();
				if (mEnemies[i]->GetHealth() <= 0)
				{
					RemoveEnemy(i);
				}
			}
		}

		if (noWall && noEnemy)
		{
			mBullets[i]->Update(dt);
		}
		else
		{
			//Remove bullet from game
			RemoveBullet(i);
		}
	}
}

void Game::enemyUpdate(float dt)
{
	for (int i = 0; i < mNrOfEnemies; i++)
	{

	}
}

Game::Game()
{
	mObstacles = new Obstacle*[5];
	mObstacles[0] = new Obstacle(5, 5);
	mObstacles[1] = new Obstacle(5, 7);
	mObstacles[2] = new Obstacle(7, 12);
	mObstacles[3] = new Obstacle(8, 4);
	mObstacles[4] = new Obstacle(12, 3);
	mNrOfObstacles = 5;
	
	mEnemies = new Enemy*[2];
	mEnemies[0] = new Enemy(13, 10);
	mEnemies[1] = new Enemy(3, 8);
	mNrOfEnemies = 2;

	mDoors = new Door*[1];
	mDoors[0] = new Door(0, 5);

	mPlayer = new Player();
}

Game::Game(Map & map)
{
	mBullets = new Bullet*[5];
	mNrOfBullets = 0;
	mNrOfObstacles = 0;
	mNrOfEnemies = 0;
	mNrOfDoors = 0;
	map.setObjects(mPlayer, mObstacles, mNrOfObstacles, mEnemies, mNrOfEnemies, mDoors, mNrOfDoors);
}

Game::~Game()
{
	for (int i = 0; i< mNrOfObstacles; i++)
	{
		delete mObstacles[i];
	}
	delete[] mObstacles;

	delete mPlayer;

	for (int i = 0; i < mNrOfBullets; i++)
	{
		delete mBullets[i];
	}
	delete[] mBullets;

	for (int i = 0; i < mNrOfEnemies; i++)
	{
		delete mEnemies[i];
	}
	delete[] mEnemies;

	for (int i = 0; i < mNrOfDoors; i++)
	{
		delete mDoors[i];
	}
	delete[] mDoors;
}

void Game::RemoveBullet(int index)
{
	if (mNrOfBullets > index)
	{
		delete mBullets[index];
		for (int i = index; i < mNrOfBullets - 1; i++)
		{
			mBullets[i] = mBullets[i + 1];
		}
		mNrOfBullets--;
	}
}

void Game::RemoveEnemy(int index)
{
	if (mNrOfEnemies > index)
	{
		delete mEnemies[index];
		for (int i = index; i < mNrOfEnemies - 1; i++)
		{
			mEnemies[i] = mEnemies[i + 1];
		}
		mNrOfEnemies--;
	}
}

void Game::Draw(RenderWindow & window)
{
	mPlayer->Draw(window);

	for (int i = 0; i<mNrOfObstacles; i++)
	{
		mObstacles[i]->Draw(window);
	}

	for (int i = 0; i<mNrOfBullets; i++)
	{
		mBullets[i]->Draw(window);
	}

	for (int i = 0; i < mNrOfEnemies; i++)
	{
		mEnemies[i]->Draw(window);
	}

	for (int i = 0; i < mNrOfDoors; i++)
	{
		mDoors[i]->Draw(window);
	}
}

void Game::Update(float dt)
{
	for (int i = 0; i<mNrOfObstacles; i++)
	{
		mObstacles[i]->Update(dt);
	}

	playerUpdate(dt);
	
	bulletUpdate(dt);

	for (int i = 0; i < mNrOfDoors; i++)
	{
		mDoors[i]->Update(dt);
	}

	//Update enemies
}
