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
// Date Revised:  16 October 2018
// Description:   State Machine
//
//
// GENERAL TODOS
//
// INCLUDES
#include "state_machine.h"


// CONSTRUCTOR
state_machine::state_machine() {

	// state machine initialization

}

// RUN MAIN LOOP
void state_machine::run(void) {


	// main loop code
	std::cout << "starting state machine...\n";

	// initialized values
	int i;
	int state = states.getState();
	int event = states.getEvent();

	std::cout << "state machine started!\n" << "status:\n" << "-state: " << state << std::endl << "-event: " << event << std::endl;

	// while currentState != ST_TERM
	//		while !eventQueue.empty()
	//			if state == currentstate or state == any state
	//				if event == currentevent or event == any event
	//					change the state


	// TODO: reorder as needed
	while (state != states.ST_TERM) {

		if (!eventQueue.empty()) {

			std::cout << "Queue has members has " << eventQueue.size() << " member(s)!\n";
			event = eventQueue.front();

			for (i = 0; i < states.transCount(); i++) {

				if ((state == states.trans[i].st) || (states.ST_ANY == states.trans[i].st)) {

					if ((event == states.trans[i].ev) || (states.EV_ANY == states.trans[i].ev)) {
						state = (states.trans[i].fn)();
						eventQueue.pop();
						break;
					}

				}

			}

		}

	}

}

// GETTERS
std::queue<b1_states::b1_event> state_machine::getEventQueue(void) {
	return eventQueue;
}

// METHODS
void state_machine::pushEvent(b1_states::b1_event pushEvent) {
	eventQueue.push(pushEvent);
};
