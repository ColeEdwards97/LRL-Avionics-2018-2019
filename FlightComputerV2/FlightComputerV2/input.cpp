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
// Date Revised:  23 October 2018
// File Name:     input.cpp
// Description:   Source file for input.h.  Defines functions that will be
//                called by threads to recieve various input types
//
// GENERAL TODOS
// TODO: add functions for all possible input types
//
// INCLUDES
#include "input.h"

int gather_input() {

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	// TODO: add a check for this
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// TODO: replace this with actual pressure transducer reading code
	int i = 0;
	while (i < 10) {


		if (i == 3 || i == 7) {
			sm.pushEvent(b1_states::EV_NOMINAL);
		}
		if (i == 4 || i == 9) {
			sm.pushEvent(b1_states::EV_OVR_PR);
		}
		if (i == 8) {
			sm.pushEvent(b1_states::EV_FULL_TEMP);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		i++;

	}

	return 0;

}

int gather_PT_input(void) {
	return 0;
}