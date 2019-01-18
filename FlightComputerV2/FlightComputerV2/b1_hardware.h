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
// Date Revised:  17 January 2018
// File Name:     b1_hardware.h
// Description:   Constructor file for b1_hardware.cpp.  Base class for solenoid
//                and pyrovalve classes
//
// GENERAL TODOS
//
// INCLUDES
#pragma once
#include "pinout.h"

class b1_hardware {

public:

	// CONSTRUCTOR
	b1_hardware();

	// METHODS
	int getHardwarePin(void);

	// VARIABLES
	int gpio_pin;

};