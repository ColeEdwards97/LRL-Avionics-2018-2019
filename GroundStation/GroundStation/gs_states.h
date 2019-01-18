#pragma once
#include <wiringPi.h>
#include <iostream>	
#include <string>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>
#include "state_machine.h"
#include "gs_hardware.h"
#include "pinout.h"

class gs_states {

public:

	// SINGLETON
	static gs_states& getInstance() {
		static gs_states instance;
		return instance;
	}
	gs_states(gs_states const&) = delete;
	void operator=(gs_states const&) = delete;

	// STATE MACHINE INSTANCE
	state_machine& sm = state_machine::getInstance();

	// ENUMS
	enum gs_state {

		ST_ANY = -1,
		ST_INIT = 1,
		ST_IDLE = 2,
		ST_TERM = 9999

	};

	enum gs_event {

		EV_ANY = -1,
		EV_INIT = 1,
		EV_IDLE = 2,
		EV_NOMINAL = 3

	};

	// STRUCTS 
	typedef struct {
		gs_state st;
		gs_event ev;
		gs_state new_st;
		gs_state(*fn)(gs_state);
	} tTransition;

	gs_states::tTransition trans[10] = {

		{ ST_INIT, EV_IDLE, ST_IDLE, &fn_init2idle },
		{ ST_ANY, EV_ANY, ST_TERM, &fn_SM_ERROR }

	};

	// METHODS
	int transCount(void);


private:

	gs_states();

	static gs_state fn_init2idle(gs_state);

	static gs_state fn_SM_ERROR(gs_state);

	// VARIABLES
	static gs_hardware* lin_act_LOX;
	static gs_hardware* lin_act_CH4;
	static gs_hardware* valve_LOX;
	static gs_hardware* valve_CH4;

};