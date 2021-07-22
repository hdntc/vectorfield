#pragma once

#include "RK4.hpp"
#include <SFML/Graphics.hpp>

class Particle {
public:
	Particle(sf::Color color, float radius, int steps, int end_time, sf::Vector2f initial_position,
		ShuntingYard::Node* x_component, ShuntingYard::Node* y_component);
	void update_position(float time);
	void draw(sf::RenderWindow& window);
	sf::Vector2f get_position();
private:
	float radius;
	int steps;
	float end_time;
	sf::Vector2f initial_position;
	sf::CircleShape form;
	ShuntingYard::Node* x_component;
	ShuntingYard::Node* y_component;
	Integrator integrator = Integrator(steps, end_time, x_component, y_component, initial_position);
};