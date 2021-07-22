#include "Button.hpp"

Button::Button(std::string button_text, sf::Vector2f size, int char_size, sf::Color bg_color, sf::Color text_color) {
	this->text.setString(button_text);
	this->text.setFillColor(text_color);
	this->text.setCharacterSize(char_size);

	this->button.setSize(size);
	this->button.setFillColor(bg_color);
}

void Button::set_font(sf::Font& font) {
	this->text.setFont(font);
}

void Button::set_back_color(sf::Color color) {
	this->button.setFillColor(color);
}

void Button::set_text_color(sf::Color color) {
	this->text.setFillColor(color);
}

void Button::set_position(sf::Vector2f pos) {
	this->button.setPosition(pos);

	float x_pos = pos.x + (button.getLocalBounds().width - text.getLocalBounds().width) / 2;
	float y_pos = pos.y + (button.getLocalBounds().height - text.getLocalBounds().height) / 2;

	this->text.setPosition({ x_pos, y_pos - text.getCharacterSize()/4});
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(this->button);
	window.draw(this->text);
}

bool Button::is_mouse_over(sf::RenderWindow& window) {
	float mouse_x = sf::Mouse::getPosition(window).x;
	float mouse_y = sf::Mouse::getPosition(window).y;

	float button_x = this->button.getPosition().x;
	float button_y = this->button.getPosition().y;

	float button_pos_width = this->button.getPosition().x + this->button.getLocalBounds().width;
	float button_pos_height= this->button.getPosition().y + this->button.getLocalBounds().height;

	return (mouse_x < button_pos_width && mouse_x > button_x && mouse_y < button_pos_height && mouse_y > button_y);
}