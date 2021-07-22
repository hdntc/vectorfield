#include "RK4.hpp"
#include <iostream>

Integrator::Integrator(int steps, float end_time, 
	ShuntingYard::Node* x_component, 
	ShuntingYard::Node* y_component, 
	sf::Vector2f initial) {
	this->steps = steps;
	this->end_time = end_time;
	this->x_component = x_component;
	this->y_component = y_component;
	this->solution[0.0f] = initial;
}

sf::Vector2f Integrator::eval_vector_function(sf::Vector2f pos) {
	return { static_cast<float>(ShuntingYard::eval(this->x_component, pos.x, pos.y)), 
			 static_cast<float>(ShuntingYard::eval(this->y_component, pos.x, pos.y)) };
}

void Integrator::integrate() {
	double h = end_time / steps;

	for (int step = 0; step < steps; step++) {
		sf::Vector2f point_1 = this->eval_vector_function(solution[step * h]);
		sf::Vector2f point_2 = this->eval_vector_function(solution[step * h] + ((float)h/2)*point_1);
		sf::Vector2f point_3 = this->eval_vector_function(solution[step * h] + ((float)h/2)*point_2);
		sf::Vector2f point_4 = this->eval_vector_function(solution[step * h] + (float)h*point_3);

		solution[h * (step + 1.f)] = solution[h * step] + ((float)h / 6) * (point_1 + 2.f * point_2 + 2.f * point_3 + point_4);
		/*std::cout << "At t=" << h*(step+1) << ": " << solution[h * (step + 1)].x << ", " << solution[h * (step + 1)].y << std::endl;*/
	}
}

sf::Vector2f Integrator::get_position(float time) {
	/*if (time > end_time) {
		std::cout << "attempt to get position out of integration range" << std::endl;
		std::cout << time << end_time << std::endl;
	}*/

	float h = end_time / steps;
	float corrected_time = h * floor(time / h); // if h=0.1 then the pos for t=1.73 wont exist, round to 1.7

	sf::Vector2f next_point = solution[h * (floor(time / h) + 1)];
	sf::Vector2f difference = next_point - solution[corrected_time];

	//std::cout << solution[corrected_time].x << ", " << solution[corrected_time].y << std::endl;

	//as a ratio between 0 and 1
	float fraction_passed = ((time - h * floor(time / h)) / h);  // this is "how far" the particle has travelled along the path between the two points


	return solution[corrected_time] + fraction_passed * difference;
}