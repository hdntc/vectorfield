#include "Field.hpp"
#include <fstream>
#include <iostream>

std::vector<std::string> get_names() {
	std::vector<std::string> result;

	std::ifstream fields_file;
	std::string line;

	fields_file.open("fields.csv");
	while (getline(fields_file, line)) {
		std::string next_name;

		for (char c : line) {
			if (c != ';') {
				next_name += c;
			}
			else {
				result.push_back(next_name);
				break;
			}
		}
	}

	return result;
}

//helper 
int find_name(std::string name) {
	std::vector<std::string> names = get_names();

	for (int i = 0; i < names.size(); i++) {
		if (names[i] == name) {
			return i;
		}
	}

	return -1; // not found
}

std::vector<std::string> split_by_semi(std::string str) {
	std::vector<std::string> result;
	std::string next_string;

	for (char c : str) {
		if (c == ';') {
			result.push_back(next_string);
			next_string = "";
		}
		else {
			next_string += c;
		}
	}

	result.push_back(next_string);

	return result;
}

Field::Field(std::string x_component, std::string y_component, int steps, float end_time, sf::Color color) {
	this->x_component = x_component;
	this->y_component = y_component;
	this->steps = steps;
	this->end_time = end_time;
	this->color = color;
}

Field::Field(std::string name) {
	int index = find_name(name);

	std::cout << index << std::endl;

	std::ifstream fields_file;
	std::string line;

	int i = 0;
	fields_file.open("fields.csv");
	while (getline(fields_file, line)) {
		if (i == index) {
			break;
		}
	}
	
	std::vector<std::string> split = split_by_semi(line);

	this->x_component = split[1];
	this->y_component = split[2];
	this->steps = stoi(split[3]);
	this->end_time = stof(split[4]);
	this->color = sf::Color(stoi(split[5]), stoi(split[6]), stoi(split[7]));
}



void Field::write(std::string name) {
	std::vector<std::string> names = get_names();

	std::ofstream fields_file;
	fields_file.open("fields.csv", std::ios_base::app);

	fields_file << name << ";" << x_component << ";" << y_component
		<< ";" << steps << ";" << end_time << ";" << (int)color.r
		<< ";" << (int)color.g << ";" << (int)color.b << "\n";

	fields_file.close();
}
