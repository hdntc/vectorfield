#include "StateMachine.hpp"

void StateMachine::push_state(state_ref new_state, bool is_replacing) {
	this->_is_adding = true;
	this->_is_replacing = is_replacing;
	this->_new_state = std::move(new_state);
}

void StateMachine::pop_state() {
	this->_is_removing = true;
}
	
void StateMachine::process() {
	if (this->_is_removing && !this->_states.empty()) {
		this->_states.pop();

		if(!this->_states.empty()) {
			this->_states.top()->resume();
		}

		this->_is_removing = false;
	}

	if (this->_is_adding) {
		if (!this->_states.empty()) {
			if (this->_is_replacing) {
				this->_states.pop();
			} else {
				this->_states.top()->pause();
			}
		}

		this->_states.push(std::move(this->_new_state));
		this->_states.top()->init();
		this->_is_adding = false;
	}
}

state_ref& StateMachine::get_active_state() {
	return this->_states.top();
}