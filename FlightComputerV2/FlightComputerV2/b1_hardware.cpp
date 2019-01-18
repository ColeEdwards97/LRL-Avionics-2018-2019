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
// File Name:     b1_hardware.cpp
// Description:   Source file for b1_hardware.h.  Gets the gpio pin used by a 
//                piece of hardware.
//
// GENERAL TODOS
//
// INCLUDES
#include "b1_hardware.h"


// CONSTRUCTORS
b1_hardware::b1_hardware() {
}

// GETTERS
int b1_hardware::getHardwarePin(void) {
	return gpio_pin;
}