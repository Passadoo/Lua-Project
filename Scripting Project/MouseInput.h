#pragma once

#include <SFML\Graphics.hpp>

class MouseInput
{
public:
	MouseInput();
	~MouseInput();

	static void Update(float delta);
	static void ProcessInput(const sf::RenderWindow &window, const sf::Event & event);
	static void ProcessMosueButtons(const sf::RenderWindow &window, const sf::Event & event);
	static void ProcessMouseWheel(const sf::Event & event);

	static bool isClicked(sf::Mouse::Button button);
	static bool isPressed(sf::Mouse::Button button);
	static bool IsReleased(sf::Mouse::Button button);
	static bool wheelUp();
	static bool wheelDown();

	static sf::Vector2i GetMousePos();
	static int GetX();
	static int GetY();

private:
	static bool mButtons[sf::Mouse::ButtonCount];
	static float mTime;
	static sf::Vector2i mMousePos;
	static sf::Vector3i mWheel;
};