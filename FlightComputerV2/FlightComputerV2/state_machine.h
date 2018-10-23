#pragma once
#include <wiringPi.h>
#include <iostream>	
#include <string>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>
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
	void pushEvent(b1_states::b1_event pushEvent);
	std::queue<b1_states::b1_event> getEventQueue(void);

	// STRUCTS
	struct b1_status {
		static b1_states::b1_state currentState;
		static b1_states::b1_event lastEvent;
	};

	// GETTERS
	b1_status getCurrentStatus(void);


private:

	// CONSTRUCTOR
	state_machine();

	// METHODS

	// reference b1_states
	b1_states& states = b1_states::getInstance();

	// VARIABLES
	std::queue<b1_states::b1_event> eventQueue;

};