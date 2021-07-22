#pragma once

#include "ShuntingYard.hpp"
#include <map>
#include <SFML/Graphics.hpp>

class Integrator {
public:
	Integrator(int steps, float end_time, ShuntingYard::Node* x_component, ShuntingYard::Node* y_component, sf::Vector2f initial);
	void integrate();
	sf::Vector2f eval_vector_function(sf::Vector2f pos);
	sf::Vector2f get_position(float time);
private:
	std::map<float, sf::Vector2f> solution; // the solution (position at given time)
	ShuntingYard::Node* x_component;        // x component of vector function
	ShuntingYard::Node* y_component;        // y component of vector function
	int steps;                              // number of integration steps to be taken
	float end_time;                           // time when simulation ends
};