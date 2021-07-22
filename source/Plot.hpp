#pragma once

#include "Textbox.hpp"
#include "Program.hpp"
#include "RK4.hpp"
#include "Particle.hpp"
#include "Button.hpp"
#include "Field.hpp"

class Plot : public State {
public:
	Plot(ProgramDataRef data);
	Plot(ProgramDataRef data, Field basis);

	void init();
	void handle_input();
	void update(float dt);
	void draw(float dt);

	void integrate();
private:
	ProgramDataRef _data;
	float time_multiplier = 0.01;
	float time = 0;
	float end_time = 0;
	int steps = 0;
	int current_input = 1;
	bool finished_integrating = false;
	bool typing_name = false;
	bool created_from_field = false;
	std::string x_text;
	std::string y_text;
	std::vector<Particle> particles;
	sf::Color particle_color;
	ShuntingYard::Node* x_component;
	ShuntingYard::Node* y_component;
	Textbox function_entry = Textbox(25, sf::Color(140, 136, 252), true);
	Textbox naming = Textbox(25, sf::Color(140, 136, 252), false);
	Button menu_button = Button("Menu", { 80, 40 }, 20, sf::Color(140, 136, 252), sf::Color::White);
	Button save_button = Button("Save", { 80, 40 }, 20, sf::Color(140, 136, 252), sf::Color::White);
	sf::Text prompt;
	sf::Text state_title;
	sf::Text simulation_time;
};