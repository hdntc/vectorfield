#include "Particle.hpp"

Particle::Particle(sf::Color color, float radius, int steps, int end_time, sf::Vector2f initial_position,
	ShuntingYard::Node* x_component, ShuntingYard::Node* y_component) {
	this->form.setFillColor(color);
	this->form.setRadius(radius);
	this->initial_position = initial_position;
	this->form.setPosition(initial_position);
	this->x_component = x_component;
	this->y_component = y_component; 
	this->steps = steps;
	this->end_time = end_time;

	this->integrator = Integrator(steps, end_time, x_component, y_component, initial_position);
	this->integrator.integrate();
}

void Particle::update_position(float time) {
	this->form.setPosition(this->integrator.get_position(time));
}

void Particle::draw(sf::RenderWindow& window) {
	window.draw(this->form);
}

sf::Vector2f Particle::get_position() {
	return this->form.getPosition();
}