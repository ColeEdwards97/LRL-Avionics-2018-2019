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
// Date Revised:  17 January 2019
// File Name:     input.cpp
// Description:   Source file for input.h.  Defines functions that will be
//                called by threads to recieve various input types
//
// GENERAL TODOS
//
// INCLUDES
#include "input.h"


// METHODS

// ... GATHER_PT_INPUT ... //
int gather_PT_input(void) {

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	int pinbase = 100;
	int i2cloc = 0x48;
	int adcbits = 16;
	int a2dval;
	float a2dvol;
	float a2dpsi;
	//float vref = 5;
	int max_LOX_pressure = 340;
	int max_CH4_pressure = 340;

	if (ads1115Setup(pinbase, i2cloc) < 0) {
		std::cout << "failed setting up I2C device :(" << std::endl;
		return -1;
	}
	else {

		std::cout << "gathering pt data..." << std::endl;

		int chan[2] = { 0, 1 };

		while(sm.isRunning()) {

			for (int j : chan) {

				a2dval = analogRead(pinbase + chan[j]);
				//a2dvol = a2dval * vref / (pow(2, (adcbits - 1)) - 1);
				a2dvol = a2dval * 4.096 / (pow(2, (adcbits - 1)) - 1);
				a2dpsi = a2dvol * 198.66f - 112.66f;

				//std::cout << "chan " << j << " " << a2dpsi << " psi" << std::endl;

				if (chan[j] == 0) {
					if (a2dpsi >= max_LOX_pressure) {
						sm.pushEvent(b1_states::b1_event::EV_OVR_PR_LOX);
					}
				}
				if (chan[j] == 1) {
					if (a2dpsi >= max_CH4_pressure) {
						sm.pushEvent(b1_states::b1_event::EV_OVR_PR_CH4);
					}
				}

			}

		}
		return 0;
	}

}

// ... GATHER_USER_INPUT ... //
int gather_user_input(void) {

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	int input;
	char confirm;

	while (sm.isRunning()) {

		std::cin >> input;

		if (input == 5) {

			std::cout << "are you sure you want to launch? Y/N" << std::endl;
			std::cin >> confirm;

			switch (confirm) {
			case 'Y':
				sm.pushEvent(static_cast<b1_states::b1_event>(input));
				break;
			case 'N':
				break;
			}

			return 0;

		}
		else if (input == 69) {
			sm.pushEvent(b1_states::b1_event::EV_OVR_PR_LOX);
			sm.pushEvent(b1_states::b1_event::EV_OVR_PR_CH4);
		}
		else {
			sm.pushEvent(static_cast<b1_states::b1_event>(input));
		}

	}

	return 0;

}