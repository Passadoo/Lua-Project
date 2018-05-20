#include "Keyboard.h"

#define IF_KEY(k, sk) else if (key == sk) return sf::Keyboard::##k;

MKeyboard::MKeyboard()
{
}

MKeyboard::~MKeyboard()
{
}

char MKeyboard::fromKeyToChar(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::A:
		return 'A';
		break;
	case sf::Keyboard::B:
		return 'B';
		break;
	case sf::Keyboard::C:
		return 'C';
		break;
	case sf::Keyboard::D:
		return 'D';
		break;
	case sf::Keyboard::E:
		return 'E';
		break;
	case sf::Keyboard::F:
		return 'F';
		break;
	case sf::Keyboard::G:
		return 'G';
		break;
	case sf::Keyboard::H:
		return 'H';
		break;
	case sf::Keyboard::I:
		return 'I';
		break;
	case sf::Keyboard::J:
		return 'J';
		break;
	case sf::Keyboard::K:
		return 'K';
		break;
	case sf::Keyboard::L:
		return 'L';
		break;
	case sf::Keyboard::M:
		return 'M';
		break;
	case sf::Keyboard::N:
		return 'N';
		break;
	case sf::Keyboard::O:
		return 'O';
		break;
	case sf::Keyboard::P:
		return 'P';
		break;
	case sf::Keyboard::Q:
		return 'Q';
		break;
	case sf::Keyboard::R:
		return 'R';
		break;
	case sf::Keyboard::S:
		return 'S';
		break;
	case sf::Keyboard::T:
		return 'T';
		break;
	case sf::Keyboard::U:
		return 'U';
		break;
	case sf::Keyboard::V:
		return 'V';
		break;
	case sf::Keyboard::W:
		return 'W';
		break;
	case sf::Keyboard::X:
		return 'X';
		break;
	case sf::Keyboard::Y:
		return 'Y';
		break;
	case sf::Keyboard::Z:
		return 'Z';
		break;
	case sf::Keyboard::Num0:
		return '0';
		break;
	case sf::Keyboard::Num1:
		return '1';
		break;
	case sf::Keyboard::Num2:
		return '2';
		break;
	case sf::Keyboard::Num3:
		return '3';
		break;
	case sf::Keyboard::Num4:
		return '4';
		break;
	case sf::Keyboard::Num5:
		return '5';
		break;
	case sf::Keyboard::Num6:
		return '6';
		break;
	case sf::Keyboard::Num7:
		return '7';
		break;
	case sf::Keyboard::Num8:
		return '8';
		break;
	case sf::Keyboard::Num9:
		return '9';
		break;
	case sf::Keyboard::Tilde:
		return '~';
		break;
	case sf::Keyboard::Dash:
		return '-';
		break;
	case sf::Keyboard::Space:
		return ' ';
		break;
	case sf::Keyboard::Period:
		return '.';
		break;
	case sf::Keyboard::Numpad0:
		return '0';
		break;
	case sf::Keyboard::Numpad1:
		return '1';
		break;
	case sf::Keyboard::Numpad2:
		return '2';
		break;
	case sf::Keyboard::Numpad3:
		return '3';
		break;
	case sf::Keyboard::Numpad4:
		return '4';
		break;
	case sf::Keyboard::Numpad5:
		return '5';
		break;
	case sf::Keyboard::Numpad6:
		return '6';
		break;
	case sf::Keyboard::Numpad7:
		return '7';
		break;
	case sf::Keyboard::Numpad8:
		return '8';
		break;
	case sf::Keyboard::Numpad9:
		return '9';
		break;
	default:
		break;
	}

	return '?';
}

sf::Keyboard::Key MKeyboard::fromCharToKey(char key)
{
	switch (key)
	{
	case 'A':
		return sf::Keyboard::A;
		break;
	case 'B':
		return sf::Keyboard::B;
		break;
	case 'C':
		return sf::Keyboard::C;
		break;
	case 'D':
		return sf::Keyboard::D;
		break;
	case 'E':
		return sf::Keyboard::E;
		break;
	case 'F':
		return sf::Keyboard::F;
		break;
	case 'G':
		return sf::Keyboard::G;
		break;
	case 'H':
		return sf::Keyboard::H;
		break;
	case 'I':
		return sf::Keyboard::I;
		break;
	case 'J':
		return sf::Keyboard::J;
		break;
	case 'K':
		return sf::Keyboard::K;
		break;
	case 'L':
		return sf::Keyboard::L;
		break;
	case 'M':
		return sf::Keyboard::M;
		break;
	case 'N':
		return sf::Keyboard::N;
		break;
	case 'O':
		return sf::Keyboard::O;
		break;
	case 'P':
		return sf::Keyboard::P;
		break;
	case 'Q':
		return sf::Keyboard::Q;
		break;
	case 'R':
		return sf::Keyboard::R;
		break;
	case 'S':
		return sf::Keyboard::S;
		break;
	case 'T':
		return sf::Keyboard::T;
		break;
	case 'U':
		return sf::Keyboard::U;
		break;
	case 'V':
		return sf::Keyboard::V;
		break;
	case 'W':
		return sf::Keyboard::W;
		break;
	case 'X':
		return sf::Keyboard::X;
		break;
	case 'Y':
		return sf::Keyboard::Y;
		break;
	case 'Z':
		return sf::Keyboard::Z;
		break;
	case '0':
		return sf::Keyboard::Num0;
		break;
	case '1':
		return sf::Keyboard::Num1;
		break;
	case '2':
		return sf::Keyboard::Num2;
		break;
	case '3':
		return sf::Keyboard::Num3;
		break;
	case '4':
		return sf::Keyboard::Num4;
		break;
	case '5':
		return sf::Keyboard::Num5;
		break;
	case '6':
		return sf::Keyboard::Num6;
		break;
	case '7':
		return sf::Keyboard::Num7;
		break;
	case '8':
		return sf::Keyboard::Num8;
		break;
	case '9':
		return sf::Keyboard::Num9;
		break;
	case '~':
		return sf::Keyboard::Tilde;
		break;
	case '-':
		return sf::Keyboard::Dash;
		break;
	case ' ':
		return sf::Keyboard::Space;
		break;
	case '.':
		return sf::Keyboard::Period;
		break;
	default:
		break;
	}

	return sf::Keyboard::Unknown;
}

sf::Keyboard::Key MKeyboard::fromStrToKey(std::string key)
{
	if (key == "A")
		return sf::Keyboard::A;
	IF_KEY(B, "B")
	IF_KEY(C, "C")
	IF_KEY(D, "D")
	IF_KEY(E, "E")
	IF_KEY(F, "F")
	IF_KEY(G, "G")
	IF_KEY(H, "H")
	IF_KEY(I, "I")
	IF_KEY(J, "J")
	IF_KEY(K, "K")
	IF_KEY(L, "L")
	IF_KEY(M, "M")
	IF_KEY(N, "N")
	IF_KEY(O, "O")
	IF_KEY(P, "P")
	IF_KEY(Q, "Q")
	IF_KEY(R, "R")
	IF_KEY(S, "S")
	IF_KEY(T, "T")
	IF_KEY(U, "U")
	IF_KEY(V, "V")
	IF_KEY(W, "W")
	IF_KEY(X, "X")
	IF_KEY(Y, "Y")
	IF_KEY(Z, "Z")

	IF_KEY(Num0, "Num0")
	IF_KEY(Num1, "Num1")
	IF_KEY(Num2, "Num2")
	IF_KEY(Num3, "Num3")
	IF_KEY(Num4, "Num4")
	IF_KEY(Num5, "Num5")
	IF_KEY(Num6, "Num6")
	IF_KEY(Num7, "Num7")
	IF_KEY(Num8, "Num8")
	IF_KEY(Num9, "Num9")
	IF_KEY(Numpad0, "Numpad0")
	IF_KEY(Numpad1, "Numpad1")
	IF_KEY(Numpad2, "Numpad2")
	IF_KEY(Numpad3, "Numpad3")
	IF_KEY(Numpad4, "Numpad4")
	IF_KEY(Numpad5, "Numpad5")
	IF_KEY(Numpad6, "Numpad6")
	IF_KEY(Numpad7, "Numpad7")
	IF_KEY(Numpad8, "Numpad8")
	IF_KEY(Numpad9, "Numpad9")

	IF_KEY(Tilde, "Tilde")
	IF_KEY(Dash, "Dash")
	IF_KEY(Space, "Space")
	IF_KEY(Period, "Period")
	IF_KEY(Enter, "Enter")
	IF_KEY(End, "End")
	IF_KEY(Home, "Home")
	IF_KEY(BackSlash, "BackSlash")
	IF_KEY(BackSpace, "BackSpace")
	IF_KEY(Right, "Right")
	IF_KEY(Left, "Left")
	IF_KEY(Up, "Up")
	IF_KEY(Down, "Down")
	IF_KEY(LShift, "LShift")
	IF_KEY(RShift, "RShift")
	IF_KEY(LControl, "LControl")
	IF_KEY(RControl, "RControl")
	else
	return sf::Keyboard::Unknown;
}

bool MKeyboard::IsKeyPressed(std::string key)
{
	return sf::Keyboard::isKeyPressed(MKeyboard::fromStrToKey(key));
}
