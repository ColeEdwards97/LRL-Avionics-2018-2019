//
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  17 January 2019
// Date Revised:  17 January 2019
// File Name:     pyrovalve.cpp
// Description:   Source file for pyrovalve.h.  Defines functions to set the
//                state of the pyrovalves.
//
//
// GENERAL TODOS
//
// INCLUDES
#include "pyrovalve.h"


// CONSTRUCTOR
pyrovalve::pyrovalve(int pin, pyrovalve::pyroType type) {

	gpio_pin = pin;
	this->type = type;
	initialize();
	
}


// METHODS

// ... initialize the pyrovalve ... //
void pyrovalve::initialize(void) {

	digitalWrite(gpio_pin, HIGH);

	switch (type)
	{
	case pyrovalve::NO:
		state = pyroState::OPEN;
		break;
	case pyrovalve::NC:
		state = pyroState::CLOSED;
		break;
	default:
		break;
	}

}

// ... detonate the pyrovalve ... //
void pyrovalve::detonate(void) {

	digitalWrite(gpio_pin, LOW);

	switch (type)
	{
	case pyrovalve::NO:
		state = pyroState::CLOSED;
		break;
	case pyrovalve::NC:
		state = pyroState::OPEN;
		break;
	default:
		break;
	}

}

// ... get the current pyrovalve state ... //
pyrovalve::pyroState pyrovalve::getCurrentState(void) {
	return state;
}