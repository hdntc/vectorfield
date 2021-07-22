#include "Menu.hpp"
#include "Field.hpp"
#include "List.hpp"

Menu::Menu(ProgramDataRef data) {
	this->_data = data;

	this->_data->asset_manager.load_font("consolas", "consola.ttf");
	this->plot_button.set_font(this->_data->asset_manager.get_font("consolas"));
	this->list_button.set_font(this->_data->asset_manager.get_font("consolas"));
	this->exit_button.set_font(this->_data->asset_manager.get_font("consolas"));

	this->title.setFont(this->_data->asset_manager.get_font("consolas"));
	this->title.setPosition({ 50, 50 });
	this->title.setCharacterSize(30);
	this->title.setString("Vector field plotter");
	this->title.setStyle(sf::Text::Style::Bold);

	this->plot_button.set_position({ 50, 200 });
	this->list_button.set_position({ 50, 300 });
	this->exit_button.set_position({ 50, 400 });
}

void Menu::init() {
	std::cout << "Menu state created!" << std::endl;

	//this->_data->asset_manager.load_texture("bg_menu", "bg_menu.PNG");
	//_background.setTexture(this->_data->asset_manager.get_texture("bg_menu"));
}

void Menu::handle_input() {
	sf::Event event;

	while (this->_data->window.pollEvent(event)) { // get events that happen (user inputs etc)
		switch (event.type) {
		case sf::Event::Closed: // clicks x in top right
			this->_data->window.close();

		case sf::Event::MouseMoved:
			for (Button* b : {&plot_button, &list_button, &exit_button}) { // iterate over references to buttons
				if (b->is_mouse_over(this->_data->window)) {
					b->set_back_color(sf::Color(42, 96, 212)); // change color if hovered over
				} else {
					b->set_back_color(sf::Color(72, 126, 242)); // else change back
				}
			}

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) { // left button released
				if (plot_button.is_mouse_over(this->_data->window)) {
					std::cout << "Plot button clicked" << std::endl;
					this->_data->state_machine.push_state(state_ref(new Plot(_data)));
				} else if(list_button.is_mouse_over(this->_data->window)) {
					std::cout << "List button clicked" << std::endl;
					this->_data->state_machine.push_state(state_ref(new List(_data)));
				} else if(exit_button.is_mouse_over(this->_data->window)) {
					std::cout << "Exit button clicked" << std::endl;
					this->_data->window.close();
				}
			}

		}
	}
}

void Menu::update(float dt) {
	
}

void Menu::draw(float dt) {
	this->_data->window.clear(sf::Color(32,32,32));
	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->title);
	this->plot_button.draw(this->_data->window);
	this->list_button.draw(this->_data->window);
	this->exit_button.draw(this->_data->window);
	this->_data->window.display();
}