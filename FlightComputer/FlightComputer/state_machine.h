#pragma once
#include <queue>
#include "b1_states.h"
#include "b1_hardware.h"

class state_machine {

public:

	// SINGLETON
	static state_machine& getInstance() {
		static state_machine instance;
		return instance;
	}
	state_machine(state_machine const&) = delete;
	void operator=(state_machine const&) = delete;


	// METHODS
	void run(void);
	std::queue<b1_states::b1_event> getEventQueue(void);
	

private:

	// CONSTRUCTOR
	state_machine();

	// reference b1_states
	b1_states& states = b1_states::getInstance();

	// VARIABLES
	std::queue<b1_states::b1_event> eventQueue;

};

