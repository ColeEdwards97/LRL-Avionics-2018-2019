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
// File Name:     pyrovalve.h
// Description:   constructor for pyrovalve.cpp.  Defines functions and
//                variables for pyrovalves and their possible states and types
//
//
// GENERAL TODOS
//
// INCLUDES
#pragma once
#include "b1_hardware.h"


class pyrovalve : public b1_hardware {

public:

	// ENUMS
	enum pyroType {
		NO = 0,
		NC = 1
	};
	enum pyroState {
		OPEN = 0,
		CLOSED = 1
	};

	// CONSTRUCTORS
	pyrovalve(int, pyroType);

	// METHODS
	void initialize(void);
	void detonate(void);

	pyroState getCurrentState(void);

private:

	// VARIABLES
	pyroType type;
	pyroState state;

};

