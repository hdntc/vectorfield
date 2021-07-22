#pragma once 

#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

struct ProgramData {
	StateMachine state_machine;
	AssetManager asset_manager;
	InputManager input_manager;

	sf::RenderWindow window;
};

typedef std::shared_ptr<ProgramData> ProgramDataRef;

class Program {
public:
	Program(int width, int height, std::string title);
private:
	const float dt = 1.0f / 60.0f; // frame rate = 60 fps
	sf::Clock _clock;
	ProgramDataRef _data = std::make_shared<ProgramData>();

	void run();
};