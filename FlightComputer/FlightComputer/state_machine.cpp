// 
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//                                                                            
// Author:        Cole Edwards
// Date Created:  11 October 2018
// Date Revised:  11 October 2018
// Description:   The main flight computer code for the Bronco 1 Launch Vehicle.
//				  This state machine handles all rocket states and possible input 
//				  events and delegates tasks to other parts of the avionics bay.
//

// GENERAL TODOS
// TODO: add hardware struct

// INCLUDES
#include <iostream>
#include <string>

// DEFINES
// defining our Bronco 1 states and events
#define ST_ANY				-1		// any possible state
#define ST_INIT				 0		// initializing flight computer items
#define ST_IDLE				 1		// rocket is idle (i.e. on launch pad)
#define ST_FILL				 2		// rocket propellant is being filled
#define ST_DRAIN			 3		// rocket is draining propellant
#define ST_IGNITION			 4		// rocket ignition 
#define ST_CRUISE			 5		// rocket is cruising
#define ST_BURN_OUT			 6		// rocket is at burn-out altitude
#define ST_VENT				 7		// rocket has vent valves open
#define ST_EMERGENCY	  8000		// emergency mode; essentially shut down rocket
#define ST_TERM			  1000		// terminate the program

#define EV_ANY				-1		// any possible event
#define EV_NOMINAL			 0		// all readings are nominal
#define EV_OVR_PR			 1		// overpressurized
#define EV_FULL_TEMP		 2		// thermocouple reading indicates tank is full


// defining what our transitions are composed of
typedef struct {

	// states and events are defined with integers
	int st;							// what state the rocket is in
	int ev;							// an event that occurs
	int(*fn)(void);					// function to run for specific transition

} tTransition;

// defining all of our functions
// TODO: Populate with appropriate task functions later
static int input1(void) {
	std::cout << "simple transition 1\n";
	return 1000;
};
static int input2(void) {
	std::cout << "simple transition 2\n";
	return 1000;
};


// build our transition table
// TODO: Populate with appropriate transitions
tTransition trans[] = {

	{ST_INIT, EV_OVR_PR, &input1},
	{ST_INIT, EV_NOMINAL, &input2}

};
#define TRANS_COUNT (sizeof(trans)/sizeof(*trans))


// returns the next event
// TODO: add code to gather output from users and hardware
int GetNextEvent(void) {
	return EV_NOMINAL;
};


// create the main state machine
// TODO: complete this pseudo code
int main() {

	int i;
	int state = ST_INIT;
	int event = EV_NOMINAL;
	while (state != ST_TERM) {

		event = GetNextEvent();

		for (i = 0; i < TRANS_COUNT; i++) {

			if ((state == trans[i].st) || (ST_ANY == trans[i].st)) {

				if ((event == trans[i].ev) || (EV_ANY == trans[i].ev)) {
					state = (trans[i].fn)();
					break;
				}

			}

		}

	}

}