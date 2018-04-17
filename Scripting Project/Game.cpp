#include "Game.h"

Game::Game()
{
	for (int i = 0; i < Defined::WORLD_WIDTH; i++)
	{
		for (int j = 0; j < Defined::WORLD_HEIGHT; j++)
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
