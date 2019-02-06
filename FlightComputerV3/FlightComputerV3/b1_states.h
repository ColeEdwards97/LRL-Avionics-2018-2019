#pragma once
#include <wiringPi.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>

#include "solenoid.h"
#include "pyrovalve.h"

class state_machine;

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
		ST_PRESSURIZED = 4,
		ST_LAUNCH = 5,
		ST_EMERG = 800,
		ST_TERM = 9999

	};

	enum b1_event {

		EV_ANY = -1,
		EV_INIT = 0,
		EV_START = 1,
		EV_FILL = 2,
		EV_PRESSURIZE = 3,
		EV_PRESSURIZED = 4,
		EV_LAUNCH = 5,
		EV_BURNOUT = 6,
		EV_OVR_PR_LOX = 701,
		EV_OVR_PR_CH4 = 702,
		EV_EMERG = 800,
		EV_CANCEL = 900

	};

	// STRUCTS
	typedef struct {
		b1_state st;
		b1_event ev;
		b1_state new_st;
		b1_state(*fn)(b1_state);
	} tTransition;

	b1_states::tTransition trans[12] = {

		{ ST_INIT,			EV_INIT,		ST_INIT,			&fn_init_init				 },	// START
		{ ST_INIT,			EV_START,		ST_IDLE,			&fn_init_idle				 }, // INITIALIZE
		{ ST_IDLE,			EV_FILL,		ST_FILL,			&fn_idle_fill				 }, // FILL
		{ ST_FILL,			EV_PRESSURIZE,	ST_PRESSURIZE,		&fn_fill_pressurize			 }, // PRESSURIZE
		{ ST_PRESSURIZE,	EV_PRESSURIZED, ST_PRESSURIZED,		&fn_pressurize_pressurized	 }, // READY
		{ ST_PRESSURIZED,	EV_LAUNCH,		ST_LAUNCH,			&fn_pressurized_launch		 }, // LAUNCH
		{ ST_LAUNCH,		EV_BURNOUT,		ST_TERM,			&fn_launch_term				 }, // BURN OUT

		{ ST_ANY,			EV_OVR_PR_LOX,	ST_ANY,				&fn_vent_LOX				 }, // VENT LOX
		{ ST_ANY,			EV_OVR_PR_CH4,	ST_ANY,				&fn_vent_CH4				 }, // VENT CH4
		{ ST_ANY,			EV_EMERG,		ST_TERM,			&fn_EMERGENCY				 },	// DRAIN
		{ ST_ANY,			EV_CANCEL,		ST_TERM,			&fn_CANCEL					 }, // CANCEL
		{ ST_ANY,			EV_ANY,			ST_TERM,			&fn_ERROR					 }	// ERROR


	};
	
	// STATE FUNCTIONS
	static b1_state fn_init_init(b1_state);
	static b1_state fn_init_idle(b1_state);
	static b1_state fn_idle_fill(b1_state);
	static b1_state fn_fill_pressurize(b1_state);
	static b1_state fn_pressurize_pressurized(b1_state);
	static b1_state fn_pressurized_launch(b1_state);
	static b1_state fn_launch_term(b1_state);

	static b1_state fn_vent_LOX(b1_state);
	static b1_state fn_vent_CH4(b1_state);
	static b1_state fn_EMERGENCY(b1_state);
	static b1_state fn_CANCEL(b1_state);
	static b1_state fn_ERROR(b1_state);

	static void vent_LOX_pressure(void);
	static void vent_CH4_pressure(void);
	static void launch_countdown(void);
	static void burnout_timer(void);
	static void drain_lines(void);

	// METHODS
	int transCount(void);

	// VARIABLES
	static solenoid* helium_LOX;
	static solenoid* helium_CH4;
	static solenoid* vent_LOX;
	static solenoid* vent_CH4;
	static pyrovalve* pyro_LOX;
	static pyrovalve* pyro_CH4;

private:

	// CONSTRUCTOR
	b1_states();

};