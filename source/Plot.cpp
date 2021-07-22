#include "Plot.hpp"
#include <iostream>
#include <random>
#include "Menu.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis1(64, 255);
std::uniform_int_distribution<> dis2(0, 255);

Plot::Plot(ProgramDataRef data) {
	this->_data = data;
	this->particle_color = sf::Color(dis2(gen), dis2(gen), dis2(gen));

	function_entry.set_font(this->_data->asset_manager.get_font("consolas"));
	function_entry.set_position({ 100, 150 });

	naming.set_font(this->_data->asset_manager.get_font("consolas"));
	naming.set_position({ 250, 500 });
	naming.set_limit(32);

	prompt.setFont(this->_data->asset_manager.get_font("consolas"));
	prompt.setString("Enter first component of the vector function:");
	prompt.setCharacterSize(20);
	prompt.setPosition({ 50, 100 });
	prompt.setStyle(sf::Text::Italic);

	state_title.setFont(this->_data->asset_manager.get_font("consolas"));
	state_title.setString("Function input");
	state_title.setCharacterSize(30);
	state_title.setPosition({ 50, 50 });
	state_title.setStyle(sf::Text::Bold);

	simulation_time.setFont(this->_data->asset_manager.get_font("consolas"));
	simulation_time.setCharacterSize(15);
	simulation_time.setPosition({ 50, 20 });
	simulation_time.setFillColor(sf::Color(140, 136, 252));

	save_button.set_font(this->_data->asset_manager.get_font("consolas"));
	this->save_button.set_position({ 150, 500 });

	this->menu_button.set_font(this->_data->asset_manager.get_font("consolas"));
	this->menu_button.set_position({ 50, 500 });
}

Plot::Plot(ProgramDataRef data, Field field) {
	this->created_from_field = true;

	this->_data = data;
	this->particle_color = field.color;
	this->end_time = field.end_time;
	this->steps = field.steps;
	this->current_input = 5;

	std::cout << field.x_component << std::endl;
	std::cout << field.y_component << std::endl;

	this->x_component = ShuntingYard::parse(ShuntingYard::reversePolishNotation(field.x_component.c_str()));
	this->y_component = ShuntingYard::parse(ShuntingYard::reversePolishNotation(field.y_component.c_str()));

	simulation_time.setFont(this->_data->asset_manager.get_font("consolas"));
	simulation_time.setCharacterSize(15);
	simulation_time.setPosition({ 50, 20 });
	simulation_time.setFillColor(sf::Color(140, 136, 252));

	state_title.setFont(this->_data->asset_manager.get_font("consolas"));
	state_title.setCharacterSize(30);
	state_title.setPosition({ 50, 50 });
	state_title.setStyle(sf::Text::Bold);

	this->menu_button.set_font(this->_data->asset_manager.get_font("consolas"));
	this->menu_button.set_position({ 50, 500 });

	integrate();
}

void Plot::integrate() {
	this->state_title.setString("Integrating...");
	this->draw(0); // show "Integrating" message before initialising particles
	// if this weren't here it would run the below block of code before re-drawing

	// create 2D grid of particles
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			Particle new_particle = Particle(sf::Color(particle_color.r, particle_color.g, particle_color.b, dis1(gen)), 
											3.f, steps, end_time, { 80.f + 35.1f * i, 60.f + 26.2f * j },
				this->x_component, this->y_component);

			new_particle.update_position(0);
			this->particles.push_back(new_particle);

		}
	}

	this->state_title.setString("");
	this->finished_integrating = true;
	this->time = 0;
}

void Plot::init() {
	std::cout << "Plot state created!" << std::endl;
}

void Plot::handle_input() {
	sf::Event event;

	while (this->_data->window.pollEvent(event)) { // get events that happen (user inputs etc)
		switch (event.type) {
		case sf::Event::Closed: // clicks x in top right
			this->_data->window.close();
		case sf::Event::TextEntered:
			if (event.text.unicode != ENTER) {
				function_entry.on_type(event);
				naming.on_type(event);
			} else {
				if (current_input == 1) {
					prompt.setString("Enter second component of vector function:");

					x_text = function_entry.get_text();

					ShuntingYard::RPN rpn = ShuntingYard::reversePolishNotation(x_text.c_str());
					this->x_component = ShuntingYard::parse(rpn);

					this->function_entry.set_text("");

					current_input++;
				} else if (current_input == 2) {
					y_text = function_entry.get_text();

					ShuntingYard::RPN rpn = ShuntingYard::reversePolishNotation(y_text.c_str());
					this->y_component = ShuntingYard::parse(rpn);

					this->function_entry.set_text("");

					prompt.setString("Enter number of steps per particle (recommended 100 to 10000)");

					current_input++;
				} else if (current_input == 3) {
					steps = stoi(function_entry.get_text());

					prompt.setString("Enter end time");

					this->function_entry.set_text("");

					current_input++;

				}
				else if (current_input == 4) {
					end_time = stof(function_entry.get_text());

					function_entry.set_selected(false);
					current_input++;

					std::cout << end_time << std::endl;
					std::cout << steps << std::endl;

					integrate();
				} else if (typing_name) {
					// add to file
					Field field = Field(x_text, y_text, steps, end_time, sf::Color(particle_color.r, particle_color.g, particle_color.b));

					field.write(naming.get_text());
				}
			}
		case sf::Event::MouseMoved: // iterate over references to buttons
		{
			for (Button* b : { &menu_button, &save_button }) {
				if (b->is_mouse_over(this->_data->window)) {
					b->set_back_color(sf::Color(110, 106, 222));
				} else {
					b->set_back_color(sf::Color(140, 136, 252));
				}
			}
		}
			

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) { // left button released
				if (menu_button.is_mouse_over(this->_data->window)) {
					std::cout << "Menu button clicked" << std::endl;
					this->_data->state_machine.push_state(state_ref(new Menu(_data)));
				} else if (save_button.is_mouse_over(this->_data->window)) {
					std::cout << "Save button clicked" << std::endl;
					this->typing_name = true;
					this->naming.set_selected(true);
				}
			}

		}
	
	}
}

void Plot::update(float dt) {
	if (finished_integrating) {
		if (dt <= 1) {
			this->time += dt * time_multiplier;
			this->simulation_time.setString("time = " + std::to_string(this->time));
		}

		for (Particle& p : particles) {
			sf::Vector2f posn = p.get_position();
			if (!(posn.x > 800.f || posn.y > 600.f || posn.x < -10.f || posn.y < -10.f)) {
				p.update_position(this->time);
			}
		}
		this->draw(1.f / 60.f);
	}

}

void Plot::draw(float dt) {
	this->_data->window.clear(sf::Color(32, 32, 32));
	this->_data->window.draw(state_title);
	this->menu_button.draw(this->_data->window);

	if (current_input <= 4) { 
		// hide UI elements when finished inputting
		this->function_entry.draw(this->_data->window);
		this->_data->window.draw(prompt);
	}

	if (finished_integrating) {
		for (Particle& p : particles) {
			p.draw(this->_data->window);
		}

		this->_data->window.draw(simulation_time);
		
		if (!created_from_field) {
			this->save_button.draw(this->_data->window);
			if (this->typing_name) {
				this->naming.draw(this->_data->window);
			}
		}
	}

	this->_data->window.display();
}