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
#include "state_machine.h"


// INSTANCE THE STATE MACHINE
state_machine& sm = state_machine::getInstance();


// TODO: create threads for input
// TODO: add code to gather output from users and hardware
//	// some list of inputs to get based on importance
//	// data collection should be run in a separate thread
//	// this function should just pull the latest value from the thread
//	// ***consider having another thread notify this thread of a change in event
int main() {

	sm.run();

}


// create the main state machine
//int main() {
//
//	int i;
//	int state = states.getState();
//	int event = states.getEvent();
//
//	while (state != states.ST_TERM) {
//
//		event = GetNextEvent();
//
//		for (i = 0; i < states.transCount(); i++) {
//
//			if ((state == states.trans[i].st) || (states.ST_ANY == states.trans[i].st)) {
//
//				if ((event == states.trans[i].ev) || (states.EV_ANY == states.trans[i].ev)) {
//					state = (states.trans[i].fn)();
//					break;
//				}
//
//			}
//
//		}
//
//	}
//
//}