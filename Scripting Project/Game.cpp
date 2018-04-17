#include "Game.h"

Game::Game()
{
	for (int i = 1; i < Defined::WORLD_WIDTH - 5; i++)
	{
		for (int j = 1; j < Defined::WORLD_HEIGHT - 5; j++)
		{
			mObstacles.push_back(new Obstacle(i, j));
		}
	}
	mPlayer = new Player();
}


Game::~Game()
{

}

void Game::Draw(RenderWindow & window)
{
	for (Obstacle* obs : mObstacles)
	{
		obs->Draw(window);
	}
	mPlayer->Draw(window);
}

void Game::Update(float dt)
{
	for (Obstacle* obs : mObstacles)
	{
		obs->Update(dt);
	}
	mPlayer->Update(dt);
}
