#pragma comment(lib, "Irrlicht.lib")
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <thread>
#include <Windows.h>
//#include <irrlicht.h>
#include <lua.hpp>
#include "lua.hpp"

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Map.h"
#include "Editor.h"
#include "MouseInput.h"

#define USE_EDITOR false

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(189);

	sf::RenderWindow window;
	window.create(sf::VideoMode(Defined::WINDOW_WIDTH, Defined::WINDOW_HEIGHT), "Scriptning Project!", sf::Style::Close | sf::Style::Resize);

	sf::Clock clock;

	Game* game = nullptr;
	Editor* editor = nullptr;

	if (USE_EDITOR)
		editor = new Editor();
	else
		game = new Game();

	sf::Time time;
	sf::Event event;
	float deltaTime = 1.0f;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (USE_EDITOR)
			{
				MouseInput::ProcessInput(window, event);
				editor->EnterText();
			}
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

		if (USE_EDITOR)
			editor->ProcessInputs();
		if (clock.getElapsedTime().asSeconds() >= 0.1f)
		{
			MouseInput::Update(deltaTime);
			if (USE_EDITOR)
				editor->Update(deltaTime);
			else
				game->Update(deltaTime, window);
			clock.restart();
		}
		if (USE_EDITOR)
			editor->Draw(window);
		else
			game->Draw(window);
		window.display();
	}

	if (game)
		delete game;
	if (editor)
		delete editor;

	return 0;
}