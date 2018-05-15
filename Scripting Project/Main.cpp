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

#define USE_EDITOR true

//void ConsoleThread(lua_State* L) {
//	char command[1000];
//	while (GetConsoleWindow()) {
//		memset(command, 0, 1000);
//		std::cin.getline(command, 1000);
//		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
//		{
//
//			std::cout << lua_tostring(L, -1) << '\n';
//			lua_pop(L, 1);
//		}
//	}
//}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(189);

	sf::RenderWindow window;
	window.create(sf::VideoMode(Defined::WINDOW_WIDTH, Defined::WINDOW_HEIGHT), "Scriptning Project!", sf::Style::Close | sf::Style::Resize);

	sf::Clock clock;

	Game* game = new Game();
	Editor* editor = new Editor();

	sf::Time time;
	sf::Event event;
	float deltaTime = 1.0f;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			MouseInput::ProcessInput(window, event);
			editor->EnterText();
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
				game->Update(deltaTime);
			clock.restart();
		}
		if (USE_EDITOR)
			editor->Draw(window);
		else
			game->Draw(window);
		window.display();
	}

	delete game;
	delete editor;

	return 0;
}