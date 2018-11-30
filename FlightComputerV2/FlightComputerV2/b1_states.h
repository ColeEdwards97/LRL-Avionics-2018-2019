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
		ST_PRESSURIZE = 3,
		ST_READY2LAUNCH = 4,
		ST_LAUNCH = 5,
		ST_CRUISE = 6,
		ST_VENT = 7,
		ST_EMERGENCY = 800,
		ST_TERM = 9999

	};

	enum b1_event {

		EV_ANY = -1,
		EV_NOMINAL = 0,
		EV_START = 1,
		EV_START_FILL = 2,
		EV_STOP_FILL = 3,
		EV_PRESSURIZED = 4,
		EV_LAUNCH = 5,
		EV_BURNOUT = 6,
		EV_OVR_PR = 700,
		EV_EMERG = 800

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

	b1_states::MPS_CONFIG conf[7] {
		// INIT, IDLE, FILLED
		{ b1_hardware::sol_state::CLOSED,
		b1_hardware::sol_state::CLOSED,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::pyro_state::INTACT,
		b1_hardware::pyro_state::INTACT,
		0,0,0,0,0,0 },
		// FILL
		{ b1_hardware::sol_state::CLOSED,
		b1_hardware::sol_state::CLOSED,
	    b1_hardware::vent_state::OPEN,
		b1_hardware::vent_state::OPEN,
		b1_hardware::pyro_state::INTACT,
		b1_hardware::pyro_state::INTACT,
		0,0,0,0,0,0	},
		// PRESSURIZE
		{ b1_hardware::sol_state::OPEN,
		b1_hardware::sol_state::OPEN,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::pyro_state::INTACT,
		b1_hardware::pyro_state::INTACT,
		0,0,0,0,0,0 },
		// LAUNCH
		{ b1_hardware::sol_state::OPEN,
		b1_hardware::sol_state::OPEN,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::pyro_state::BURST,
		b1_hardware::pyro_state::BURST,
		0,0,0,0,0,0 },
		// VENT
		{ b1_hardware::sol_state::HOLD,
		b1_hardware::sol_state::HOLD,
		b1_hardware::vent_state::OPEN,
		b1_hardware::vent_state::OPEN,
		b1_hardware::pyro_state::HOLD,
		b1_hardware::pyro_state::HOLD,
		0,0,0,0,0,0 },
		// HOLD
		{ b1_hardware::sol_state::HOLD,
		b1_hardware::sol_state::HOLD,
		b1_hardware::vent_state::HOLD,
		b1_hardware::vent_state::HOLD,
		b1_hardware::pyro_state::HOLD,
		b1_hardware::pyro_state::HOLD,
		0,0,0,0,0,0 },
		// DRAIN
		{ b1_hardware::sol_state::OPEN,
		b1_hardware::sol_state::OPEN,
		b1_hardware::vent_state::OPEN,
		b1_hardware::vent_state::OPEN,
		b1_hardware::pyro_state::BURST,
		b1_hardware::pyro_state::BURST,
		0,0,0,0,0,0 }

	};

	typedef struct {
		b1_state st;
		b1_event ev;
		MPS_CONFIG conf;
		b1_state new_st;
		b1_state(*fn)(MPS_CONFIG, b1_state);
	} tTransition;

	b1_states::tTransition trans[10] = {
		// TODO: create appropriate state functions
		{ ST_INIT,			EV_START,		conf[1],	ST_IDLE,			fn1 },
		{ ST_IDLE,			EV_START_FILL,	conf[2],	ST_FILL,			fn1 },
		{ ST_FILL,			EV_STOP_FILL,	conf[3],	ST_PRESSURIZE,		fn1	},
		{ ST_PRESSURIZE,	EV_PRESSURIZED, conf[3],	ST_READY2LAUNCH,	fn1 },
		{ ST_READY2LAUNCH,	EV_LAUNCH,		conf[4],	ST_LAUNCH,			fn1 },
		{ ST_LAUNCH,		EV_NOMINAL,		conf[7],	ST_CRUISE,			fn1	},
		{ ST_CRUISE,		EV_BURNOUT,		conf[5],	ST_TERM,			fn1 },
		{ ST_ANY,			EV_NOMINAL,     conf[6],    currentState,		fn1 },	// HOLD
		{ ST_ANY,			EV_OVR_PR,		conf[5],	currentState,		fn1 },	// VENT
		{ ST_ANY,			EV_EMERG,		conf[7],	ST_EMERGENCY,		fn1 }	// DRAIN

	};

	// METHODS
	static b1_state fn1(MPS_CONFIG, b1_state);
	static b1_state fn2(MPS_CONFIG, b1_state);

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