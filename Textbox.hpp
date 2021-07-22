#pragma once

#include <sstream>
#include <SFML/Graphics.hpp>

#define BACKSPACE 8 // ascii code for backspace
#define ENTER 13

class Textbox {
public:
	Textbox(int size, sf::Color color, bool selected);
	void set_font(sf::Font& font);
	void set_position(sf::Vector2f pos);
	void set_limit(bool limited);
	void set_limit(int limit);
	void set_selected(bool selected);
	void set_text(std::string str);
	std::string get_text();
	void draw(sf::RenderWindow& window);
	void on_type(sf::Event event);
private:
	sf::Text textbox;
	std::ostringstream text;
	bool is_selected = false;
	bool has_limit = false;
	int limit;

	void input_logic(int char_typed);
	void delete_last_char();
};