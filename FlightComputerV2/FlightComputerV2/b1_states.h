#pragma once
#include <wiringPi.h>
#include <iostream>	
#include <string>
#include <unistd.h>
#include <cstdio>
#include "b1_hardware.h"

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
		b1_hardware::sol_state ss1;
		b1_hardware::sol_state ss2;
		b1_hardware::vent_state vs1;
		b1_hardware::vent_state vs2;
		b1_hardware::pyro_state ps1;
		b1_hardware::pyro_state ps2;
	} MPS_CONFIG;

	b1_states::MPS_CONFIG conf[1]{
		{ b1_hardware::sol_state::CLOSED,
		b1_hardware::sol_state::CLOSED,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::vent_state::CLOSED,
		b1_hardware::pyro_state::INTACT,
		b1_hardware::pyro_state::INTACT }
	};

	typedef struct {
		b1_state st;
		b1_event ev;
		MPS_CONFIG conf;
		b1_state(*fn)(void);
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

	static b1_state fn1(void);
	static b1_state fn2(void);

	int transCount(void);

private:

	// CONSTRUCTOR 
	b1_states();

	b1_state currentState;
	b1_event currentEvent;

};