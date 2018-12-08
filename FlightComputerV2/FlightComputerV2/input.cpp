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

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	// TODO: add check to make sure sm is running

	int pinbase = 100;
	int i2cloc = 0x48;
	int a2dval;
	float a2dvol;
	float a2dpsi;
	float vref = 5;

	std::cout << "gathering pt data..." << std::endl;

	if (ads1115Setup(pinbase, i2cloc) < 0) {
		std::cout << "failed setting up I2C device" << std::endl;
		return -1;
	}
	else {

		int chan[2] = { 0,1 };

		while(sm.isRunning()) {

			for (int j : chan) {

				a2dval = analogRead(pinbase + chan[j]);
				a2dvol = a2dval * vref / 65536;
				a2dpsi = a2dvol * 198.66 - 112.66;

				std::cout << "chan " << j << " " << a2dpsi << " psi" << std::endl;

				//if (a2dpsi >= 400) {
				//	sm.pushEvent(b1_states::b1_event::EV_OVR_PR);
				//}
				//else {
				//	sm.pushEvent(b1_states::b1_event::EV_NOMINAL);
				//}

			}

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
	char confirm;

	while (sm.isRunning()) {

		std::cout << "next event:" << std::endl;
		std::cin >> input;

		if (input == 5) {

			std::cout << "are you sure you want to launch? Y/N" << std::endl;
			std::cin >> confirm;

			switch (confirm) {
			case 'Y':
				std::cout << "BRONCO ONE IS LAUNCHING!" << std::endl;
				sm.pushEvent(static_cast<b1_states::b1_event>(input));
				break;
			case 'N':
				break;
			}

		}
		else {
			sm.pushEvent(static_cast<b1_states::b1_event>(input));
		}

	}

	return 0;

}