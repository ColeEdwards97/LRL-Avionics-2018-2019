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
// Date Revised:  16 October 2018
// Description:   The main flight computer code for the Bronco 1 Launch Vehicle.
//				  This state machine handles all rocket states and possible input 
//				  events and delegates tasks to other parts of the avionics bay.
//
//
// GENERAL TODOS
// TODO: Implement multi-threading (use <queue>)
//
// INCLUDES
#include <iostream>
#include <string>
#include <thread>
#include "state_machine.h"


// INSTANCE THE STATE MACHINE
state_machine& sm = state_machine::getInstance();


void gather_input(void) {
	
	// for testing only!
	int in;
	do {
		std::cin >> in;
		b1_states::b1_event ev = static_cast<b1_states::b1_event>(in);
		sm.pushEvent(ev);
	} while (in != 0);
	
}

// TODO: create threads for input
// TODO: add code to gather output from users and hardware
//	// some list of inputs to get based on importance
//	// data collection should be run in a separate thread
//	// this function should just pull the latest value from the thread
//	// ***consider having another thread notify this thread of a change in event
int main() {

	// start the thread that gathers system inputs
	std::thread th_INPUT(gather_input);

	// run the finite state machine
	// add a return in state machine for status
	// while(status)...
	sm.run();

	// wait until input thread finishes
	th_INPUT.join();

	return 0;

}