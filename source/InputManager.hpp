#pragma once

#include <SFML/Graphics.hpp>

class InputManager {
public:
	InputManager() {};
	~InputManager() {};

	bool is_sprite_clicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
	sf::Vector2i get_mouse_position(sf::RenderWindow& window);
};