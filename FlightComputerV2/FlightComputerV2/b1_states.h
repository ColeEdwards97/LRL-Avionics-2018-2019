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
// Date Revised:  14 December 2018
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
#include <thread>
#include <chrono>
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
		EV_OVR_PR = 700,
		EV_EMERG = 800

	};

	// STRUCTS

	typedef struct {
		b1_state st;
		b1_event ev;
		b1_state new_st;
		b1_state(*fn)(b1_state);
	} tTransition;

	b1_states::tTransition trans[10] = {
		{ ST_INIT,			EV_START,		ST_IDLE,			fn_init2idle		 }, // INITIALIZE
		{ ST_IDLE,			EV_START_FILL,	ST_FILL,			fn_idle2fill		 }, // FILL
		{ ST_FILL,			EV_STOP_FILL,	ST_PRESSURIZE,		fn_fill2pressurize	 }, // PRESSURIZE
		{ ST_PRESSURIZE,	EV_PRESSURIZED, ST_READY2LAUNCH,	fn_pressurized2ready }, // READY
		{ ST_READY2LAUNCH,	EV_LAUNCH,		ST_LAUNCH,			fn_ready2launch		 }, // LAUNCH
		{ ST_LAUNCH,		EV_NOMINAL,		ST_CRUISE,			fn_launch2cruise	 }, // CRUISE
		{ ST_CRUISE,		EV_NOMINAL,		ST_TERM,			fn_cruise2term		 }, // BURN OUT

		{ ST_ANY,			EV_NOMINAL,     currentState,		fn_hold				 },	// HOLD
		{ ST_ANY,			EV_OVR_PR,		currentState,		fn_vent				 },	// VENT
		{ ST_ANY,			EV_EMERG,		ST_TERM,			fn_emergency		 }	// DRAIN

	};

	// METHODS
	static b1_state fn_init2idle(b1_state);
	static b1_state fn_idle2fill(b1_state);
	static b1_state fn_fill2pressurize(b1_state);
	static b1_state fn_pressurized2ready(b1_state);
	static b1_state fn_ready2launch(b1_state);
	static b1_state fn_launch2cruise(b1_state);
	static b1_state fn_cruise2term(b1_state);
	static b1_state fn_hold(b1_state);
	static b1_state fn_vent(b1_state);
	static b1_state fn_emergency(b1_state);

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