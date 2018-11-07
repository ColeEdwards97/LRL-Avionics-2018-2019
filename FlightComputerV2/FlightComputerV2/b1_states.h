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
// Date Revised:  06 November 2018
// File Name:     b1_states.h
// Description:   Constructor file for b1_states.cpp.  Defines the possible
//                states, events, transitions, and transition functions for the
//                Bronco One.  The theory here is that there should exist a 
//                transition for any possible flight case which determines the
//                behavior of the Bronco One.
//
// GENERAL TODOS
//
// INCLUDES
#pragma once
#include <wiringPi.h>
#include <iostream>	
#include <string>
#include <unistd.h>
#include <cstdio>
#include "b1_hardware.h"
#include "pinout.h"

class b1_states {

public:

	// SINGLETON
	static b1_states& getInstance() {
		static b1_states instance;
		return instance;
	}
	b1_states(b1_states const&) = delete;
	void operator=(b1_states const&) = delete;

	// ENUMS
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

	enum b1_event {

		EV_ANY = -1,
		EV_NOMINAL = 0,
		EV_OVR_PR = 1,
		EV_USR_FILL = 2,
		EV_USR_LAUNCH = 3,
		EV_FULL_TEMP = 299

	};

	// STRUCTS
	typedef struct {
		b1_hardware::sol_state ss1;
		b1_hardware::sol_state ss2;
		b1_hardware::vent_state vs1;
		b1_hardware::vent_state vs2;
		b1_hardware::pyro_state ps1;
		b1_hardware::pyro_state ps2;
		int wait_ss1;
		int wait_ss2;
		int wait_vs1;
		int wait_vs2;
		int wait_ps1;
		int wait_ps2;
	} MPS_CONFIG;

	b1_states::MPS_CONFIG conf[1] {
		{ b1_hardware::sol_state::CLOSED,
		b1_hardware::sol_state::CLOSED,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::pyro_state::INTACT,
		b1_hardware::pyro_state::INTACT,
		0,0,0,0,0,0 }
	};

	typedef struct {
		b1_state st;
		b1_event ev;
		MPS_CONFIG conf;
		b1_state(*fn)(MPS_CONFIG);
	} tTransition;

	b1_states::tTransition trans[3] = {
		{ ST_ANY, EV_FULL_TEMP, conf[1], fn1 },
		{ ST_ANY, EV_OVR_PR, conf[1], fn2 },
		{ ST_ANY, EV_NOMINAL, conf[1], fn2 }
	};

	// METHODS
	b1_state getState(void);
	b1_event getEvent(void);
	void setState(b1_state newState);
	void setEvent(b1_event newEvent);

	static b1_state fn1(MPS_CONFIG);
	static b1_state fn2(MPS_CONFIG);

	int transCount(void);

private:

	// CONSTRUCTOR 
	b1_states();

	// VARIABLES
	b1_state currentState;
	b1_event currentEvent;

	static b1_hardware* sol_1;
	static b1_hardware* sol_2;
	static b1_hardware* vent_1;
	static b1_hardware* vent_2;
	static b1_hardware* pyro_1;
	static b1_hardware* pyro_2;

};