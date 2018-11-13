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
// Date Revised:  13 November 2018
// File Name:     pinout.cpp
// Description:   Source file for pinout.h.  Initializes the GPIO pins to their
//                proper state.
//
// GENERAL TODOS
//
// INCLUDES
#include "pinout.h"

// Initialize the pins to the appropriate mode
int initialize_pins() {

	std::cout << "exporting pins" << std::endl;

	wiringPiSetupGpio();

	int i;
	for (i = 0; i < pin_count(); i++) {
	
		pinMode(pin_init[i].pin, pin_init[i].mode);
	
	}

	return 0;

}

int cleanup(void) {

	int i;
	for (i = 0; i < pin_count(); i++) {

		digitalWrite(pin_init[i].pin, LOW);

	}

	return 0;

}

// Count the number of pin configurations to set
int pin_count(void) {
	return (sizeof(pin_init) / sizeof(*pin_init));
}
