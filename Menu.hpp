#pragma once

#include "State.hpp"
#include "Button.hpp"
#include "Plot.hpp"
#include "Program.hpp"

class Menu : public State {
public:
	Menu(ProgramDataRef data);

	void init();
	void handle_input();
	void update(float dt);
	void draw(float dt);
private:
	ProgramDataRef _data;
	sf::Clock _clock;
	sf::Sprite _background;
	Button plot_button = Button("Plot", { 80, 40 }, 20, sf::Color(72, 126, 242), sf::Color::White);
	Button list_button = Button("List", { 80, 40 }, 20, sf::Color(72, 126, 242), sf::Color::White);
	Button exit_button = Button("Exit", { 80, 40 }, 20, sf::Color(72, 126, 242), sf::Color::White);
	sf::Text title;
};