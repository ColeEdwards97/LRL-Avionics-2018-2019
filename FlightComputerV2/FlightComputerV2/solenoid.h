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
// File Name:     solenoid.h
// Description:   Constructor file for solenoid.cpp.  Defines the functions and
//                variables that set the state and type of the solenoids.
//
//
// GENERAL TODOS
//
// INCLUDES
#pragma once
#include "b1_hardware.h"


class solenoid : public b1_hardware {

public:
	
	// ENUMS
	enum solenoidType {
		NO = 0,
		NC = 1
	};
	enum solenoidState {
		OPEN = 0,
		CLOSED = 1
	};
	enum solenoidUse {
		HELIUM = 0,
		VENT = 1
	};
	enum solenoidLine {
		LOX = 0,
		CH4 = 1
	};

	// CONSTRUCTORS
	solenoid(int, solenoidType);
	solenoid(int, solenoidType, solenoidState, solenoidUse, solenoidLine);

	// METHODS
	void open(void);
	void close(void);
	void toggle(void);

	solenoidState getCurrentState(void);
	void setCurrentState(solenoidState);

private:

	// VARIABLES
	solenoidType type;
	solenoidState state;
	solenoidUse use;
	solenoidLine line;
	
};

