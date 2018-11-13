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
// File Name:     b1_states.cpp
// Description:   Source file for b1_states.h.  Defines the functions to get 
//                and set the state of the Bronco One.
//
// GENERAL TODOS
//
// INCLUDES
#include "b1_states.h"

b1_hardware* b1_states::sol_1 = new b1_hardware(PIN_SOL_1, b1_hardware::hardware::SOLENOID);
b1_hardware* b1_states::sol_2 = new b1_hardware(PIN_SOL_2, b1_hardware::hardware::SOLENOID);
b1_hardware* b1_states::vent_1 = new b1_hardware(PIN_VENT_1, b1_hardware::hardware::VENT);
b1_hardware* b1_states::vent_2 = new b1_hardware(PIN_VENT_2, b1_hardware::hardware::VENT);
b1_hardware* b1_states::pyro_1 = new b1_hardware(PIN_PYRO_1, b1_hardware::hardware::PYRO);
b1_hardware* b1_states::pyro_2 = new b1_hardware(PIN_PYRO_2, b1_hardware::hardware::PYRO);

// Construct and initialize the B1 states
b1_states::b1_states() {

	currentState = b1_state::ST_INIT;
	currentEvent = b1_event::EV_NOMINAL;

}

// GETTERS
b1_states::b1_state b1_states::getState(void) {
	return currentState;
}
b1_states::b1_event b1_states::getEvent(void) {
	return currentEvent;
}

// SETTERS
void b1_states::setState(b1_state newState) {
	currentState = newState;
}
void b1_states::setEvent(b1_event newEvent) {
	currentEvent = newEvent;
}

// Get the number of transitions
int b1_states::transCount(void) {
	return (sizeof(trans) / sizeof(*trans));
}

// Define the B1 state functions
b1_states::b1_state b1_states::fn1(b1_states::MPS_CONFIG conf) {
	std::cout << "ST_TERM\n";

	// wait conf.wait1
	sol_1->setSolState(conf.ss1);
	// wait
	sol_2->setSolState(conf.ss2);
	// wait
	vent_1->setVentState(conf.vs1);
	// wait
	vent_2->setVentState(conf.vs2);
	// wait
	pyro_1->setPyroState(conf.ps1);
	// wait
	pyro_2->setPyroState(conf.ps2);

	return ST_TERM;
}
b1_states::b1_state b1_states::fn2(b1_states::MPS_CONFIG conf) {
	std::cout << "ST_CRUISE\n";

	// wait conf.wait1
	sol_1->setSolState(conf.ss1);
	// wait
	sol_2->setSolState(conf.ss2);
	// wait
	vent_1->setVentState(conf.vs1);
	// wait
	vent_2->setVentState(conf.vs2);
	// wait
	pyro_1->setPyroState(conf.ps1);
	// wait
	pyro_2->setPyroState(conf.ps2);

	return ST_CRUISE;
}