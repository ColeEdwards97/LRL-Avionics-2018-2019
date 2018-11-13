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
// Date Revised:  13 November 2018
// File Name:     state_machine.h
// Description:   Constructor file for state_machine.cpp.  Initializes the 
//                methods to be used in the state machine.  Implements the 
//                Singleton pattern.
//
// GENERAL TODOS
//
// INCLUDES
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

	bool isReadyToPressurize;
	bool isReadyToLaunch;

};