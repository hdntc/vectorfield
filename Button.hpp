#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button(std::string button_text, sf::Vector2f size, int char_size, sf::Color bg_color, sf::Color text_color);
	void set_font(sf::Font& font);
	void set_back_color(sf::Color color);
	void set_text_color(sf::Color color);
	void set_position(sf::Vector2f pos);
	void draw(sf::RenderWindow& window);
	bool is_mouse_over(sf::RenderWindow& window);
	sf::Text text;
private:
	sf::RectangleShape button;
};