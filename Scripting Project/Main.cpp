#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Map.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window;
	window.create(sf::VideoMode(Defined::WINDOW_WIDTH, Defined::WINDOW_HEIGHT), "Scriptning Project!", sf::Style::Close | sf::Style::Resize);

	sf::Clock clock;

	Game* game = new Game();

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
		window.clear(sf::Color(140, 100, 230, 255));
		if (clock.getElapsedTime().asSeconds() >= 0.1f)
		{
			game->Update(1.0f);
			clock.restart();
		}
		game->Draw(window);
		window.display();
	}

	delete game;

	return 0;
}