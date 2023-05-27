#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

class InputHandler
{
public:
	static bool GetKey(sf::Keyboard::Key keycode);
	static bool GetMouseButton(sf::Mouse::Button keycode);
};

