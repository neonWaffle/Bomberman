#include "InputHandler.h"

bool InputHandler::GetKey(sf::Keyboard::Key keycode)
{
	return sf::Keyboard::isKeyPressed(keycode);
}

bool InputHandler::GetMouseButton(sf::Mouse::Button keycode)
{
	return sf::Mouse::isButtonPressed(keycode);
}

