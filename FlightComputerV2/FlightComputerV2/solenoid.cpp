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
// Date Revised:  28 January 2019
// File Name:     solenoid.cpp
// Description:   Source file for solenoid.h.  Defines the functions that set
//                the state of the solenoids.
//
//
// GENERAL TODOS
//
// INCLUDES
#include "solenoid.h"
#include "state_machine.h"

// INSTANCE STATE MACHINE
state_machine& sol_sm = state_machine::getInstance();


// CONSTRUCTORS
solenoid::solenoid(int pin, solenoid::solenoidType type) {

	this->gpio_pin = pin;
	this->type = type;
	setCurrentState(solenoidState::CLOSED);

}
solenoid::solenoid(int pin, 
	solenoid::solenoidType type, 
	solenoid::solenoidState state,
	solenoid::solenoidUse use, 
	solenoid::solenoidLine line) {

	this->gpio_pin = pin;
	this->type = type;
	this->use = use;
	this->line = line;
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
	this->state = solenoidState::OPEN;

	// tell the state machine if we are venting or not
	if (this->use == solenoidUse::VENT) {
		switch (this->line)
		{
		case solenoid::LOX:
			sol_sm.bVentingLOX = true;
			break;
		case solenoid::CH4:
			sol_sm.bVentingCH4 = true;
			break;
		default:
			break;
		}
	}

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
	this->state = solenoidState::CLOSED;

	// tell the state machine if we are venting or not
	if (this->use == solenoidUse::VENT) {
		switch (line)
		{
		case solenoid::LOX:
			sol_sm.bVentingLOX = false;
			break;
		case solenoid::CH4:
			sol_sm.bVentingCH4 = false;
			break;
		default:
			break;
		}
	}

}

// ... toggle the solenoid's state ... //
void solenoid::toggle(void) {
	
	switch (this->state)
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
	return this->state;
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