#pragma comment(lib, "Irrlicht.lib")
#ifdef _DEBUG
#pragma comment(lib, "LuaLibd.lib")
#else
#pragma comment(lib, "Lualib.lib")
#endif

#include <thread>
#include <Windows.h>
#include <irrlicht.h>
#include <lua.hpp>
#include "lua.hpp"

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Map.h"
#include "Editor.h"

#define USE_EDITOR true

void ConsoleThread(lua_State* L) {
	char command[1000];
	while (GetConsoleWindow()) {
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
		{

			std::cout << lua_tostring(L, -1) << '\n';
			lua_pop(L, 1);
		}
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	std::thread conThread(ConsoleThread, L);

	irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16, false, false, true, 0);
	if (!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", irr::core::rect<irr::s32>(10, 10, 260, 22), true);



	sf::RenderWindow window;
	window.create(sf::VideoMode(Defined::WINDOW_WIDTH, Defined::WINDOW_HEIGHT), "Scriptning Project!", sf::Style::Close | sf::Style::Resize);

	sf::Clock clock;

	Game* game = new Game();
	Editor* editor = new Editor();

	sf::Time time;
	sf::Event event;
	while (window.isOpen() && device->run())
	{
		driver->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					device->closeDevice();
				}
			}
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				device->closeDevice();
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
			if (USE_EDITOR)
				editor->Update(1.0f, window);
			else
				game->Update(1.0f);
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

	device->drop();

	conThread.join();

	return 0;
}