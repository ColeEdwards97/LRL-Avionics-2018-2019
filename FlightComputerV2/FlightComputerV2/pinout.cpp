//
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  06 November 2018
// Date Revised:  17 January 2019
// File Name:     pinout.cpp
// Description:   Source file for pinout.h.  Initializes the GPIO pins to their
//                proper state.
//
// GENERAL TODOS
//
// INCLUDES
#include "pinout.h"

// STRUCTS
static pins pin_init[6] = {
	{ PIN_HELIUM_LOX,  OUTPUT, HIGH },
	{ PIN_HELIUM_CH4,  OUTPUT, HIGH },
	{ PIN_VENT_LOX, OUTPUT, HIGH },
	{ PIN_VENT_CH4, OUTPUT, HIGH },
	{ PIN_PYRO_LOX, OUTPUT, HIGH },
	{ PIN_PYRO_CH4, OUTPUT, HIGH }
};

// METHODS

// ... initialize pins ... //
int initialize_pins() {

	std::cout << "exporting pins" << std::endl;

	wiringPiSetupGpio();

	int i;
	for (i = 0; i < pin_count(); i++) {
	
		pinMode(pin_init[i].pin, pin_init[i].mode);	// initialize the pins with the corresponding pin mode
		digitalWrite(pin_init[i].pin, pin_init[i].state); // set the default state of the pin
	
	}

	return 0;

}

// ... cleanup pins ... //
int cleanup(void) {

	int i;
	for (i = 0; i < pin_count(); i++) {

		digitalWrite(pin_init[i].pin, LOW);
		// TODO: this will open all valves... should we open them all at the end?
	}

	return 0;

}

// ... Count the number of pin configurations to set ... //
int pin_count(void) {
	return (sizeof(pin_init) / sizeof(*pin_init));
}
