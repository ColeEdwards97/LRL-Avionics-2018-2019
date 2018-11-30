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
// File Name:     b1_hardware.cpp
// Description:   Source file for b1_hardware.h.  Defines the functions to get 
//                and set a hardware's state.
//
// GENERAL TODOS
//
// INCLUDES
#include "b1_hardware.h"


// CONSTRUCTORS
b1_hardware::b1_hardware(int pin) {

	gpio_pin = pin;
	hardwareType = hardware::NONE;
	currentSolState = sol_state::CLOSED;
	currentVentState = vent_state::CLOSED;
	currentPyroState = pyro_state::INTACT;

}
b1_hardware::b1_hardware(int pin, b1_hardware::hardware type) {

	gpio_pin = pin;
	hardwareType = type;
	
	switch (type)
	{
	case b1_hardware::hardware::NONE:
		break;
	case b1_hardware::hardware::SOLENOID:
		currentSolState = sol_state::CLOSED;
		break;
	case b1_hardware::hardware::VENT:
		currentVentState = vent_state::CLOSED;
		break;
	case b1_hardware::hardware::PYRO:
		currentPyroState = pyro_state::INTACT;
		break;
	default:
		break;
	}

}

// GETTERS
int b1_hardware::getHardwarePin(void) {
	return gpio_pin;
}
b1_hardware::hardware b1_hardware::getHardwareType(void) {
	return hardwareType;
}
b1_hardware::sol_state b1_hardware::getSolState(void) {
	return currentSolState;
}
b1_hardware::vent_state b1_hardware::getVentState(void) {
	return currentVentState;
}
b1_hardware::pyro_state b1_hardware::getPyroState(void) {
	return currentPyroState;
}

// SETTERS
void b1_hardware::setHardwareType(b1_hardware::hardware newHardware) {
	if (hardwareType == hardware::NONE) {
		hardwareType = newHardware;
	}
}

// STATE SETTERS

// ... SOLENOIDS ... //
void b1_hardware::setSolState(b1_hardware::sol_state newState) {

	switch (newState)
	{
	case b1_hardware::sol_state::ERROR:
		// report error
		break;
	case b1_hardware::sol_state::HOLD:
		// make no changes
		break;
	case b1_hardware::sol_state::CLOSED:
		// set GPIO pin to high state
		digitalWrite(gpio_pin, HIGH);
		break;
	case b1_hardware::sol_state::OPEN:
		// set GPIO pin to low state
		digitalWrite(gpio_pin, LOW);
		break;
	default:
		break;
	}

	currentSolState = newState;
}
// ... VENTS ... //
void b1_hardware::setVentState(b1_hardware::vent_state newState) {

	switch (newState)
	{
	case b1_hardware::vent_state::ERROR:
		// report error
		break;
	case b1_hardware::vent_state::HOLD:
		// make no changes
		break;
	case b1_hardware::vent_state::CLOSED:
		// set GPIO pin to high state
		digitalWrite(gpio_pin, HIGH);
		break;
	case b1_hardware::vent_state::OPEN:
		// set GPIO pin to low state
		digitalWrite(gpio_pin, LOW);
		break;
	default:
		break;
	}

	currentVentState = newState;
}
// ... PYROS ... //
void b1_hardware::setPyroState(b1_hardware::pyro_state newState) {

	switch (newState)
	{
	case b1_hardware::pyro_state::ERROR:
		// report error
		break;
	case b1_hardware::pyro_state::HOLD:
		// make no changes
		break;
	case b1_hardware::pyro_state::INTACT:
		// do nothing
		break;
	case b1_hardware::pyro_state::BURST:
		// set GPIO pin to low a few times to ensure pyro is burst
		digitalWrite(gpio_pin, LOW);
		break;
	default:
		break;
	}

	currentPyroState = newState;
}