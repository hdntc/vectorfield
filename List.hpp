#pragma once

#include "Program.hpp"
#include "RK4.hpp"
#include "Particle.hpp"
#include "Button.hpp"
#include "Field.hpp"

class List : public State {
public:
	List(ProgramDataRef data);

	void init();
	void handle_input();
	void update(float dt);
	void draw(float dt);
private:
	ProgramDataRef _data;
	std::vector<Button> buttons;
	Button menu_button = Button("Menu", { 80, 40 }, 20, sf::Color(140, 136, 252), sf::Color::White);
};