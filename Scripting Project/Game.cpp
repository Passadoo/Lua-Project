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

		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfObstacles(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetObstacle(i)->GetPos().x == nextPos.x && mDungeon->GetCurrentRoom().GetObstacle(i)->GetPos().y == nextPos.y)
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

		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfObstacles(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetObstacles()[i]->GetPos().x == nextPos.x && mDungeon->GetCurrentRoom().GetObstacles()[i]->GetPos().y == nextPos.y)
			{
				noWall = false;
			}
		}

		bool noEnemy = true;
		for (int i = 0; i < mDungeon->GetCurrentRoom().GetNrOfEnemies(); i++)
		{
			if (mDungeon->GetCurrentRoom().GetEnemies()[i]->GetPos().x == nextPos.x && mDungeon->GetCurrentRoom().GetEnemies()[i]->GetPos().y == nextPos.y)
			{
				noEnemy = false;
				mDungeon->GetCurrentRoom().GetEnemies()[i]->TakeDamage();
				if (mDungeon->GetCurrentRoom().GetEnemies()[i]->GetHealth() <= 0)
				{
					mDungeon->GetCurrentRoom().RemoveEnemy(i);
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
	//for (int i = 0; i < mRoom->GetNrOfEnemies(); i++)
	//{

	//}
}

Game::Game()
{
	mBullets = new Bullet*[5];
	mNrOfBullets = 0;
	mPlayer = new Player(2, 2);
	mDungeon = new Dungeon();
	mDungeon->LoadCurrentRoom();
	//std::cout << mDungeon->GetCurrentRoom().GetNrOfObstacles() << std::endl;
	//mRoom = new Room("StartRoom.txt", true, false, false, false);
	//mRoom->LoadRoom();
}

Game::~Game()
{
	for (int i = 0; i < mNrOfBullets; i++)
	{
		delete mBullets[i];
	}
	delete[] mBullets;

	delete mPlayer;
	delete mDungeon;
	//delete mRoom;
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
	for (int i = 0; i<mNrOfBullets; i++)
	{
		mBullets[i]->Draw(window);
	}

	mPlayer->Draw(window);
	mDungeon->Draw(window);
}

void Game::Update(float dt)
{
	mDungeon->Update(dt);
	playerUpdate(dt);
	bulletUpdate(dt);

	//mRoom->Update(dt);
}
