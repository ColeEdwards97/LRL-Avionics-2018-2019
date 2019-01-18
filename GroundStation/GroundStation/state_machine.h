#pragma once
#include <iostream>	
#include <string>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>
#include <queue>
#include "gs_states.h"

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
	void pushEvent(gs_states::gs_event pushEvent);
	std::queue<gs_states::gs_event> getEventQueue(void);
	
	bool isRunning(void);

	// GETTERS
	gs_states::gs_state getCurrentState(void);
	gs_states::gs_event getCurrentEvent(void);

	// SETTERS
	void setCurrentState(gs_states::gs_state);
	void setCurrentEvent(gs_states::gs_event);

private:

	state_machine();

	// reference gs_states
	gs_states& states = gs_states::getInstance();

	// VARIABLES

	std::queue<gs_states::gs_event> eventQueue;

	gs_states::gs_state currentState;
	gs_states::gs_event currentEvent;

	bool is_running;

};