#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(Defined::WINDOW_WIDTH, Defined::WINDOW_HEIGHT), "Scriptning Project!", sf::Style::Close | sf::Style::Resize);

	sf::Clock clock;

	Game* game = new Game();

	Player mPlayer(0, 0);
	Obstacle mObstacle(5, 5);

	sf::Time time;
	sf::Event event;
	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::LostFocus:
				break;
			}
		}

		//sf::CircleShape shape(50);
		//shape.setFillColor(sf::Color(100, 250, 50));

		window.clear(sf::Color(140, 100, 230, 255));
		//window.draw(shape);
		if (clock.getElapsedTime().asSeconds() >= 0.01f)
		{
			//mPlayer.Update(1.0f);
			//mObstacle.Update(1.0f);
			game->Update(1.0f);
			clock.restart();
		}
		game->Draw(window);
		//mPlayer.Draw(window);
		//mObstacle.Draw(window);
		window.display();
	}

	return 0;
}