#include "ShuntingYard.hpp"
#pragma once

#include <SFML/Graphics.hpp>

class Field {
public:
	Field(std::string x_component, std::string y_component, int steps, float end_time, sf::Color color);
	Field(std::string name);
	void write(std::string name); // writes to 
	std::string x_component;
	std::string y_component;
	int steps;
	float end_time;
	sf::Color color;
};

int find_name(std::string name);
std::vector<std::string> split_by_semi(std::string str);
std::vector<std::string> get_names();