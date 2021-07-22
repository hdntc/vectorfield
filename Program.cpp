#include "Program.hpp"
#include "Menu.hpp"

Program::Program(int width, int height, std::string title) {
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	_data->state_machine.push_state(state_ref(new Menu(this->_data)));

	this->run();
}

void Program::run() {
	float new_time;
	float frame_time;
	float interpolation;

	float current_time = this->_clock.getElapsedTime().asSeconds();
	float acc = 0.0f;

	while (this->_data->window.isOpen()) {
		this->_data->state_machine.process();
		new_time = this->_clock.getElapsedTime().asSeconds();

		frame_time = new_time - current_time;
		current_time = new_time;
		acc += frame_time;

		while (acc >= dt) {
			this->_data->state_machine.get_active_state()->handle_input();
			this->_data->state_machine.get_active_state()->update(dt);

			acc -= dt;
		}

		interpolation = acc / dt;
		this->_data->state_machine.get_active_state()->draw(interpolation);
	}
}