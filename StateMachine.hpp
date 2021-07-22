#pragma once

#include <memory>
#include <stack>
#include "State.hpp"

typedef std::unique_ptr<State> state_ref;

class StateMachine {
public:
	StateMachine() {}
	~StateMachine() {}
	void push_state(state_ref new_state, bool is_replacing = true);
	void pop_state();
	void process();
	state_ref& get_active_state();

private:
	std::stack<state_ref> _states;
	state_ref _new_state;
	bool _is_removing;
	bool _is_adding;
	bool _is_replacing;
};