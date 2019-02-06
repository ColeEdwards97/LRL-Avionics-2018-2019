//
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  23 October 2018
// Date Revised:  17 January 2019
// File Name:     state_machine.h
// Description:   Constructor file for state_machine.cpp.  Initializes the 
//                methods to be used in the state machine.  Implements the 
//                Singleton pattern.
//
// GENERAL TODOS
//
// INCLUDES
#pragma once
#include <iostream>	
#include <string>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>
#include <queue>
#include <condition_variable>

#include "b1_states.h"

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
	void pushEvent(b1_states::b1_event);
	std::queue<b1_states::b1_event> getEventQueue(void);

	bool isRunning(void);
	bool isVentingLOX(void);
	bool isVentingCH4(void);
	void setIsVentingLOX(bool);
	void setIsVentingCH4(bool);

	// GETTERS
	b1_states::b1_state getCurrentState(void);
	b1_states::b1_event getCurrentEvent(void);
	b1_states::b1_state getPreviousState(void);
	void setCurrentState(b1_states::b1_state);
	void setCurrentEvent(b1_states::b1_event);

	// VARIABLES
	std::condition_variable cv_isRunning;
	std::mutex mtx_isRunning;

	bool bVentingLOX;
	bool bVentingCH4;

private:

	// CONSTRUCTOR
	state_machine();

	// METHODS

	// reference b1_states
	b1_states& states = b1_states::getInstance();

	// VARIABLES
	std::queue<b1_states::b1_event> eventQueue;

	b1_states::b1_state currentState;
	b1_states::b1_event currentEvent;
	b1_states::b1_state previousState;

	bool is_running;

};