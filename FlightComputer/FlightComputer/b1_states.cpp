// 
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//                
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  11 October 2018
// Date Revised:  12 October 2018
// Description:   Bronco 1 States definition
//
//
// GENERAL TODOS
// 
//
// INCLUDES
#include "b1_states.h"

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

// Define the B1 functions
int b1_states::fn1(void) {
	std::cout << "ST_TERM\n";

	int j = 1;
	for each (MPS_CONFIG i in b1_states::getInstance().conf) {
		std::cout << j << std::endl;
		j++;
	}

	return ST_TERM;
}