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
// Date Revised:  28 January 2019
// File Name:     state_machine.cpp
// Description:   Source file for state_machine.h.  Defines the overall behavior
//                of the Flight Computer.  Essentially, the state machine is the
//                main thread that accepts input via the <queue> module and 
//                determines the course of action based on these inputs using
//                the transition table in b1_states.h.  The loop that it runs
//                in is defined below.  This state machine is an implementation 
//                of a Finite State Machine.  This implementation accepts 
//                'wildcards', meaning it includes the case that the Bronco One
//                is either in ANY state, or recieves ANY input event.  On each
//                loop, the state machine checks the event queue which is
//                populated on another thread by the methods in input.h and
//                input.cpp.  The latest event is then evaluated and the state
//                machine moves on to the next event in the queue.
//
// GENERAL TODOS
//
// INCLUDES
#include "state_machine.h"


// CONSTRUCTOR
state_machine::state_machine() {

	// state machine initialization
	currentState = b1_states::b1_state::ST_INIT;
	currentEvent = b1_states::b1_event::EV_INIT;
	previousState = currentState;
	pushEvent(currentEvent);

	is_running = false;
	bVentingLOX = false;
	bVentingCH4 = false;

}

// RUN MAIN LOOP
void state_machine::run(void) {

	is_running = true;
	cv_isRunning.notify_all();

	std::cout << "starting state machine...\n";

	// while currentState != ST_TERM
	//		while !eventQueue.empty()
	//			if state == currentstate or state == any state
	//				if event == currentevent or event == any event
	//					change the state

	while (currentState != states.ST_TERM) {

		if (!eventQueue.empty()) {

			currentEvent = eventQueue.front();

			for (int i = 0; i < states.transCount(); i++) {

				if (currentState == states.trans[i].st || states.ST_ANY == states.trans[i].st) {

					if (currentEvent == states.trans[i].ev || states.EV_ANY == states.trans[i].ev) {
						previousState = currentState;
						currentState = (states.trans[i].fn)(states.trans[i].new_st);
						eventQueue.pop();
						break;

					}

				}

			}

		}

	}
	is_running = false;
}

// GETTERS
std::queue<b1_states::b1_event> state_machine::getEventQueue(void) {
	return eventQueue;
};
b1_states::b1_state state_machine::getCurrentState(void) {
	return currentState;
};
b1_states::b1_event state_machine::getCurrentEvent(void) {
	return currentEvent;
}
b1_states::b1_state state_machine::getPreviousState(void) {
	return previousState;
}

// SETTERS
void state_machine::setCurrentState(b1_states::b1_state newState) {
	currentState = newState;
}
void state_machine::setCurrentEvent(b1_states::b1_event newEvent) {
	currentEvent = newEvent;
}

// METHODS
void state_machine::pushEvent(b1_states::b1_event pushEvent) {
	eventQueue.push(pushEvent);
}
bool state_machine::isRunning(void) {
	return is_running;
}
bool state_machine::isVentingLOX(void) {
	return bVentingLOX;
}
bool state_machine::isVentingCH4(void) {
	return bVentingCH4;
}
void state_machine::setIsVentingLOX(bool ventingLOX) {
	bVentingLOX = ventingLOX;
}
void state_machine::setIsVentingCH4(bool ventingCH4) {
	bVentingCH4 = ventingCH4;
}