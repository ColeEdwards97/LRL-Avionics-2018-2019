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
// File Name:     solenoid.cpp
// Description:   Source file for solenoid.h.  Defines the functions that set
//                the state of the solenoids.
//
//
// GENERAL TODOS
//
// INCLUDES
#include "solenoid.h"


// CONSTRUCTORS
solenoid::solenoid(int pin, solenoid::solenoidType type) {

	gpio_pin = pin;
	this->type = type;
	setCurrentState(solenoidState::CLOSED);

}
solenoid::solenoid(int pin, solenoid::solenoidType type, solenoid::solenoidState state) {

	gpio_pin = pin;
	this->type = type;
	setCurrentState(state);

}

// METHODS

// ... open the solenoid ... //
void solenoid::open(void) {
	
	switch (type)
	{
	case solenoid::NO:
		digitalWrite(this->gpio_pin, HIGH);
		break;
	case solenoid::NC:
		digitalWrite(this->gpio_pin, LOW);
		break;
	default:
		break;
	}
	state = solenoidState::OPEN;

}

// ... close the solenoid ... //
void solenoid::close(void) {
	
	switch (type)
	{
	case solenoid::NO:
		digitalWrite(this->gpio_pin, LOW);
		break;
	case solenoid::NC:
		digitalWrite(this->gpio_pin, HIGH);
		break;
	default:
		break;
	}
	state = solenoidState::CLOSED;
}

// ... toggle the solenoid's state ... //
void solenoid::toggle(void) {
	
	switch (state)
	{
	case solenoid::OPEN:
		this->close();
		break;
	case solenoid::CLOSED:
		this->open();
		break;
	default:
		break;
	}

}

// ... get the current solenoid state ... //
solenoid::solenoidState solenoid::getCurrentState(void) {
	return state;
}

// ... set the current solenoid state ... //
void solenoid::setCurrentState(solenoid::solenoidState new_state) {
	
	switch (new_state)
	{
	case solenoid::OPEN:
		this->open();
		break;
	case solenoid::CLOSED:
		this->close();
		break;
	default:
		break;
	}

}