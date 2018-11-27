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
// Date Revised:  26 November 2018
// File Name:     input.cpp
// Description:   Source file for input.h.  Defines functions that will be
//                called by threads to recieve various input types
//
// GENERAL TODOS
// TODO: add functions for all possible input types
// TODO: consider spawning threads after state machine has started
//
// INCLUDES
#include "input.h"


// METHODS
// TODO: test method. remove later
int gather_input() {

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	if (!sm.isRunning) {
		// TODO: add a try statement?
		return -1;
	}

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

// TODO: put into its own thread
int gather_PT_input(void) {

	int pinbase = 100;
	int i2cloc = 0x48;
	int a2dval;
	float a2dvol;
	float vref = 5;
	int a2dchannel = 0;

	std::cout << "gathering pt data..." << std::endl;

	if (ads1115Setup(pinbase, i2cloc) < 0) {
		std::cout << "failed setting up I2C device" << std::endl;
		return -1;
	}
	else {
		for (int i = 0; i < 10; i++) {
			a2dval = analogRead(pinbase + a2dchannel);
			a2dvol = a2dval * vref / 4096;
			std::cout << "value: " << a2dval << std::endl;
			std::cout << "voltatge: " << a2dvol << std::endl;
		}
		return 0;
	}

}

// TODO: put into its own thread
int gather_user_input(void) {

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	if (!sm.isRunning) {
		// TODO: add a try statement?
		return -1;
	}

	int input;

	for (int i = 0; i < 10; i++) {

		std::cout << "next event:" << std::endl;
		std::cin >> input;

		b1_states::b1_event event = static_cast<b1_states::b1_event>(input);

		sm.pushEvent(event);

	}

	return 0;

}