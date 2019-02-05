#pragma once
#include <wiringPi.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>


class b1_states
{
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
		ST_PRESSURIZING = 3,
		ST_READYTOLAUNCH = 4,
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
		EV_LAUNCH = 4,
		EV_OVR_PR_LOX = 701,
		EV_OVR_PR_CH4 = 702,
		EV_EMERG = 800

	};

	// STRUCTS
	typedef struct {
		b1_state st;
		b1_event ev;
		b1_state new_st;
		b1_state(*fn)(b1_state);
	} tTransition;


private:

	b1_states();
};

