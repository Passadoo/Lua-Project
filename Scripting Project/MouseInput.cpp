#include "MouseInput.h"


bool MouseInput::mButtons[] = { false };
float MouseInput::mTime = 0;
sf::Vector2i MouseInput::mMousePos;
sf::Vector3i MouseInput::mWheel;

MouseInput::MouseInput()
{
}

MouseInput::~MouseInput()
{
}

void MouseInput::Update(float delta)
{
	if (mTime > 0.0f)
		mTime -= delta;
	else
		mTime = 0.0f;
}

void MouseInput::ProcessInput(const sf::RenderWindow & window, const sf::Event & event)
{
	ProcessMosueButtons(window, event);
	ProcessMouseWheel(event);
}

void MouseInput::ProcessMosueButtons(const sf::RenderWindow &window, const sf::Event & event)
{
	mMousePos = sf::Mouse::getPosition(window);
	if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
	{
		for (int i = 0; i < sf::Mouse::ButtonCount; i++)
		{
			sf::Mouse::Button button = (sf::Mouse::Button)i;
			if (event.mouseButton.button == button && event.type == sf::Event::MouseButtonPressed)
			{
				mButtons[button] = true;
				mTime = 2;
			}
			if (event.mouseButton.button == button && event.type == sf::Event::MouseButtonReleased)
			{
				mButtons[button] = false;
			}
		}
	}
}

void MouseInput::ProcessMouseWheel(const sf::Event & event)
{
	if (event.type == sf::Event::MouseWheelMoved)
	{
		mWheel.x = event.mouseWheel.x;
		mWheel.y = event.mouseWheel.y;
		mWheel.z = event.mouseWheel.delta;
	}
}

bool MouseInput::isClicked(sf::Mouse::Button button)
{
	return mButtons[button] && mTime > 0.0f;
}

bool MouseInput::isPressed(sf::Mouse::Button button)
{
	return mButtons[button];
}

bool MouseInput::IsReleased(sf::Mouse::Button button)
{
	return !mButtons[button];
}

bool MouseInput::wheelUp()
{
	bool changed = mWheel.z > 0;
	if (changed)
		mWheel.z = 0;
	return changed;
}

bool MouseInput::wheelDown()
{
	bool changed = mWheel.z < 0;
	if (changed)
		mWheel.z = 0;
	return changed;
}

sf::Vector2i MouseInput::GetMousePos()
{
	return mMousePos;
}

int MouseInput::GetX()
{
	return mMousePos.x;
}

int MouseInput::GetY()
{
	return mMousePos.y;
}
