#include "Game.h"

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
	map.setObjects(mPlayer, mObstacles, mNrOfObstacles);
}


Game::~Game()
{
	for (int i = 0; i< mNrOfObstacles; i++)
	{
		delete mObstacles[i];
	}
	delete mPlayer;
}

void Game::Draw(RenderWindow & window)
{
	for (int i = 0; i<mNrOfObstacles; i++)
	{
		mObstacles[i]->Draw(window);
	}
	mPlayer->Draw(window);
}

void Game::Update(float dt)
{
	for (int i = 0; i<mNrOfObstacles; i++)
	{
		mObstacles[i]->Update(dt);
	}

	bool moveInit = false;
	Vector2f nextPos;

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		nextPos = Vector2f(mPlayer->GetPos().x + Defined::GRID_CELL_SIZE, mPlayer->GetPos().y);
		moveInit = true;
		mPlayer->SetDirection(Player::RIGHT);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		nextPos = Vector2f(mPlayer->GetPos().x, mPlayer->GetPos().y + Defined::GRID_CELL_SIZE);
		moveInit = true;
		mPlayer->SetDirection(Player::DOWN);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		nextPos = Vector2f(mPlayer->GetPos().x - Defined::GRID_CELL_SIZE, mPlayer->GetPos().y);
		moveInit = true;
		mPlayer->SetDirection(Player::LEFT);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		nextPos = Vector2f(mPlayer->GetPos().x, mPlayer->GetPos().y - Defined::GRID_CELL_SIZE);
		moveInit = true;
		mPlayer->SetDirection(Player::UP);
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
