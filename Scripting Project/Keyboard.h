#pragma once

#include <SFML\Graphics.hpp>
#include "ILuaMember.h"

class MKeyboard : public ILuaMember
{
public:
	MKeyboard();
	~MKeyboard();

	static char fromKeyToChar(sf::Keyboard::Key key);
	static sf::Keyboard::Key fromCharToKey(char key);
	static sf::Keyboard::Key fromStrToKey(std::string key);

	bool IsKeyPressed(std::string key);
private:

};