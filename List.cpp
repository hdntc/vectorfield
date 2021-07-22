#include "List.hpp"
#include "Menu.hpp"

List::List(ProgramDataRef data) {
	this->_data = data;

	std::vector<std::string> names = get_names();

	this->menu_button.set_font(this->_data->asset_manager.get_font("consolas"));
	this->menu_button.set_position({ 50, 500 });

	int i = 0;
	for (std::string s : names) {
		Button new_button = Button(s, { 320, 40 }, 15, sf::Color(192, 30, 60), sf::Color::White);
		new_button.set_font(this->_data->asset_manager.get_font("consolas"));
		new_button.set_position({ 50.f, 50.f + 80.f * i });
		this->buttons.push_back(new_button);
		
		i++;
	};
}

void List::handle_input() {
	sf::Event event;

	while (this->_data->window.pollEvent(event)) { // get events that happen (user inputs etc)
		switch (event.type) {
		case sf::Event::Closed: // clicks x in top right
			this->_data->window.close();

		case sf::Event::MouseMoved: {
			for (Button& b : buttons) {
				if (b.is_mouse_over(this->_data->window)) {
					b.set_back_color(sf::Color(222, 60, 90)); // change color if hovered over
				}
				else {
					b.set_back_color(sf::Color(192, 30, 60)); // else change back
				}
			}

			if (menu_button.is_mouse_over(this->_data->window)) {
				menu_button.set_back_color(sf::Color(110, 106, 222));
			}
			else {
				menu_button.set_back_color(sf::Color(140, 136, 252));
			}
		}

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) { // left button released
				if (menu_button.is_mouse_over(this->_data->window)) {
					std::cout << "Menu button clicked" << std::endl;
					this->_data->state_machine.push_state(state_ref(new Menu(_data)));
				}

				for (Button& b : buttons) {
					if (b.is_mouse_over(this->_data->window)) {
						std::cout << b.text.getString().toAnsiString() << std::endl;
						this->_data->state_machine.push_state(state_ref(new Plot(_data, b.text.getString().toAnsiString())));
					}
				}
			} 

		}
	}
}

void List::init() {
	std::cout << "List state created!" << std::endl;

	//this->_data->asset_manager.load_texture("bg_menu", "bg_menu.PNG");
	//_background.setTexture(this->_data->asset_manager.get_texture("bg_menu"));
}

void List::update(float dt) {

}

void List::draw(float dt) {
	this->_data->window.clear(sf::Color(32, 32, 32));

	for (Button& b : buttons) {
		b.draw(this->_data->window);
	}

	this->menu_button.draw(this->_data->window);

	this->_data->window.display();
}