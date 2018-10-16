// 
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//                
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  15 October 2018
// Date Revised:  15 October 2018
// Description:   State Machine
//
//
// GENERAL TODOS
//
// INCLUDES
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
	void pushEvent(b1_states::b1_event pushEvent);
	std::queue<b1_states::b1_event> getEventQueue(void);
	

private:

	// CONSTRUCTOR
	state_machine();

	// METHODS

	// reference b1_states
	b1_states& states = b1_states::getInstance();

	// VARIABLES
	std::queue<b1_states::b1_event> eventQueue;

};

