// 
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//                
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  11 October 2018
// Date Revised:  12 October 2018
// Description:   Bronco 1 States definition
//
//
// GENERAL TODOS
// TODO: add hardware struct
//
// INCLUDES
#pragma once
#include <iostream>

class b1_states {

public:

	// ENUMS
	// B1 States
	enum b1_state {

		ST_ANY = -1,
		ST_INIT = 0,
		ST_IDLE = 1,
		ST_FILL = 2,
		ST_DRAIN = 3,
		ST_IGNITION = 4,
		ST_CRUISE = 5,
		ST_BURN_OUT = 6,
		ST_VENT = 7,
		ST_EMERGENCY = 8001,
		ST_TERM = 9999

	};

	// B1 Events
	enum b1_event {

		EV_ANY = -1,
		EV_NOMINAL = 0,
		EV_OVR_PR = 1,
		EV_FULL_TEMP = 2

	};

	// STRUCTS
	typedef struct {
		b1_state st;
		b1_event ev;
		int(*fn)(void);
	} tTransition;

	// Populate transitions table
	b1_states::tTransition trans[2] = {
		{ST_INIT, EV_FULL_TEMP, fn1},
		{ST_INIT, EV_OVR_PR, fn1}
	};

	// CONSTRUCTOR
	b1_states();

	// METHODS
	void setState(b1_state newState);
	void setEvent(b1_event newEvent);
	b1_state getState(void);
	b1_event getEvent(void);

	static int fn1(void);

	int transCount(void);

private:

	b1_state currentState;
	b1_event currentEvent;

};