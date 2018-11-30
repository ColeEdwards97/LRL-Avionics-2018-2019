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
// Date Revised:  29 November 2018
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
	// TODO: add check to make sure sm is running

	int input;

	while (sm.isRunning()) {

		std::cout << "next event:" << std::endl;
		std::cin >> input;

		sm.pushEvent(static_cast<b1_states::b1_event>(input));

	}

	return 0;

}