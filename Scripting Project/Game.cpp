#include "Game.h"

void Game::playerUpdate(float dt)
{
	bool moveInit = false;
	Vector2f nextPos;

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		nextPos = Vector2f(mPlayer->GetPos().x + Defined::GRID_CELL_SIZE, mPlayer->GetPos().y);
		moveInit = true;
		mPlayer->SetDirection(Defined::RIGHT);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		nextPos = Vector2f(mPlayer->GetPos().x, mPlayer->GetPos().y + Defined::GRID_CELL_SIZE);
		moveInit = true;
		mPlayer->SetDirection(Defined::DOWN);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		nextPos = Vector2f(mPlayer->GetPos().x - Defined::GRID_CELL_SIZE, mPlayer->GetPos().y);
		moveInit = true;
		mPlayer->SetDirection(Defined::LEFT);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		nextPos = Vector2f(mPlayer->GetPos().x, mPlayer->GetPos().y - Defined::GRID_CELL_SIZE);
		moveInit = true;
		mPlayer->SetDirection(Defined::UP);
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
	std:cout << "Space pressed" << std::endl;
		if (mNrOfBullets < 5)
		{
			mBullets[mNrOfBullets] = new Bullet(mPlayer->GetPos().x, mPlayer->GetPos().y, mPlayer->GetDirection());
			if (mBullets[mNrOfBullets])
			{
				std::cout << "Bullet created. " + std::to_string(mNrOfBullets + 1) + " bullets exist" << std::endl;
			}
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
			mBullets[i]->Update(dt);
		}
		else
		{
			//Deal damage to enemies

			//Remove bullet from game
			RemoveBullet(i);
		}
	}


	//Check for bullet collisions
}

Game::Game()
{
	mObstacles = new Entity*[5];
	mObstacles[0] = new Obstacle(5, 5);
	mObstacles[1] = new Obstacle(5, 7);
	mObstacles[2] = new Obstacle(7, 12);
	mObstacles[3] = new Obstacle(8, 4);
	mObstacles[4] = new Obstacle(12, 3);
	mNrOfObstacles = 5;

	mPlayer = new Player();
}

Game::Game(Map & map)
{
	mBullets = new Bullet*[5];
	mNrOfBullets = 0;
	mNrOfObstacles = 0;
	map.setObjects(mPlayer, mObstacles, mNrOfObstacles);


}

Game::~Game()
{
	for (int i = 0; i< mNrOfObstacles; i++)
	{
		delete mObstacles[i];
	}
	delete[] mObstacles;

	delete mPlayer;

	for (int i = 0; i<mNrOfBullets; i++)
	{
		delete mBullets[i];
	}
	delete[] mBullets;
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

void Game::Draw(RenderWindow & window)
{
	for (int i = 0; i<mNrOfObstacles; i++)
	{
		mObstacles[i]->Draw(window);
	}
	mPlayer->Draw(window);

	for (int i = 0; i<mNrOfBullets; i++)
	{
		mBullets[i]->Draw(window);
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
}
