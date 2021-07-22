#include "Textbox.hpp"

Textbox::Textbox(int size, sf::Color color, bool selected) {
	this->textbox.setCharacterSize(size);
	this->textbox.setFillColor(color);
	this->is_selected = selected;
	
	if (selected) {
		textbox.setString("_");
	} else {
		textbox.setString("");
	}
}

void Textbox::input_logic(int char_typed) {
	if (char_typed == BACKSPACE) {
		if (text.str().length() > 0) {
			this->delete_last_char();
		}
	} else if (char_typed != ENTER) {
		text << static_cast<char>(char_typed);
	}

	textbox.setString(text.str() + "_");
}

void Textbox::delete_last_char() {
	std::string temp = text.str();
	std::string new_text = "";

	for (int i = 0; i < temp.length() - 1; i++) {
		//add all characters except for last one
		new_text += temp[i]; 
	}

	text.str(""); // clear current text
	text << new_text; // append to text
}

void Textbox::set_font(sf::Font& font) {
	this->textbox.setFont(font);
}

void Textbox::set_position(sf::Vector2f pos) {
	this->textbox.setPosition(pos);
}

void Textbox::set_limit(bool limited) {
	this->has_limit = limited;
}

void Textbox::set_limit(int limit) {
	this->has_limit = true;
	this->limit = limit;
}

void Textbox::set_selected(bool selected) {
	this->is_selected = selected;
	textbox.setString(text.str() + "_");

	if (!selected) {
		// if its not selected we dont want the _ at the end
		std::string temp = text.str();
		std::string new_text = "";

		for (int i = 0; i < temp.length() - 1; i++) {
			//add all characters except for last one
			new_text += temp[i];
		}
		textbox.setString(new_text);
	}
}

void Textbox::set_text(std::string str) {
	text.str(""); // clear texsdt stream to nothing
	text << str; // append full string to new stream
	textbox.setString(str+"_"); // set displayed text to the string
}

std::string Textbox::get_text() {
	return this->text.str();
}

void Textbox::draw(sf::RenderWindow& window) {
	window.draw(textbox);
}

void Textbox::on_type(sf::Event event) {
	if (this->is_selected) {
		int char_typed = event.text.unicode;
		if (char_typed < 128) { 
			// allow ascii only
			if (this->has_limit) {
				if (text.str().length() <= limit) {
					this->input_logic(char_typed);
				} else if(text.str().length() > limit && char_typed == BACKSPACE) {
					//allow them to delete chracters when over the limit
					this->delete_last_char();
				}
			} else {
				this->input_logic(char_typed);
			}
		}
	}
}