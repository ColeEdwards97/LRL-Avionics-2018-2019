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
// Date Revised:  17 January 2019
// File Name:     b1_states.cpp
// Description:   Source file for b1_states.h.  Defines the functions to get 
//                and set the state of the Bronco One.
//
// GENERAL TODOS
// TODO: vent in a separate detached thread to prevent clogging the state machine
//
// INCLUDES
#include "b1_states.h"
#include "state_machine.h"

// CREATE THE B1 HARDWARE
solenoid* b1_states::helium_LOX = new solenoid(PIN_HELIUM_LOX, solenoid::NC);
solenoid* b1_states::helium_CH4 = new solenoid(PIN_HELIUM_CH4, solenoid::NC);
solenoid* b1_states::vent_LOX = new solenoid(PIN_VENT_LOX, solenoid::NC);
solenoid* b1_states::vent_CH4 = new solenoid(PIN_VENT_CH4, solenoid::NO);
pyrovalve* b1_states::pyro_LOX = new pyrovalve(PIN_PYRO_LOX, pyrovalve::NC);
pyrovalve* b1_states::pyro_CH4 = new pyrovalve(PIN_PYRO_CH4, pyrovalve::NC);

// INSTANCE STATE MACHINE
state_machine& state_mach = state_machine::getInstance();

// CONSTRUCTOR
b1_states::b1_states() {
}

// METHODS
int b1_states::transCount(void) {
	return (sizeof(trans) / sizeof(*trans));
}

// B1 STATE FUNCTIONS

// ... fn_init ... //
b1_states::b1_state b1_states::fn_init(b1_states::b1_state new_state) {

	std::cout << "State Machine started successfully" << std::endl;
	return new_state;

}

// ... fn_init2idle ... //
b1_states::b1_state b1_states::fn_init2idle(b1_states::b1_state new_state) {

	helium_LOX->close();
	helium_CH4->close();
	vent_LOX->close();
	vent_CH4->close();

	std::cout << "Bronco One has been initialized..." << std::endl;
	std::cout << "Waiting to begin filling..." << std::endl;
	return new_state;

}

// ... fn_idle2fill ... //
b1_states::b1_state b1_states::fn_idle2fill(b1_states::b1_state new_state) {

	vent_LOX->open();
	vent_CH4->open();

	std::cout << "Bronco One is ready to be filled" << std::endl;
	std::cout << "Begin filling sequence" << std::endl;
	return new_state;

}

// ... fn_fill2pressurize ... //
b1_states::b1_state b1_states::fn_fill2pressurize(b1_states::b1_state new_state) {

	vent_LOX->close();
	vent_CH4->close();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	helium_LOX->open();
	helium_CH4->open();

	std::cout << "Bronco One is being pressurized..." << std::endl;
	return new_state;

}

// ... fn_pressurized2ready ... //
b1_states::b1_state b1_states::fn_pressurized2ready(b1_states::b1_state new_state) {

	std::cout << "Bronco One is pressurized and ready to launch." << std::endl;
	std::cout << "Waiting on your go..." << std::endl;
	return new_state;

}

// ... fn_ready2launch ... //
b1_states::b1_state b1_states::fn_ready2launch(b1_states::b1_state new_state) {

	std::cout << "Bronco One is launching in..." << std::endl;
	
	launch_countdown();

	pyro_LOX->detonate();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	pyro_CH4->detonate();

	std::thread(burnout_timer).detach();

	return new_state;

}

// ... fn_launch2cruise ... //
b1_states::b1_state b1_states::fn_launch2term(b1_states::b1_state new_state) {

	helium_LOX->open();
	helium_CH4->open();
	vent_LOX->open();
	vent_CH4->open();

	std::cout << "Bronco One has successfully launched..." << std::endl;
	std::cout << "Good luck on recovery :)" << std::endl;

	return new_state;

}

// ... fn_vent_LOX ... //
b1_states::b1_state b1_states::fn_vent_LOX(b1_states::b1_state new_state) {
	
	std::cout << "Venting LOX line" << std::endl;

	// open LOX vent valve
	vent_LOX->open();
	// wait for 3 seconds
	std::this_thread::sleep_for(std::chrono::seconds(3));
	// close LOX vent valve
	vent_CH4->close();
	
	return state_mach.getPreviousState();

}

// ... fn_vent_CH4 ... //
b1_states::b1_state b1_states::fn_vent_CH4(b1_states::b1_state new_state) {

	std::cout << "Venting CH4 line" << std::endl;

	// open CH4 vent valve
	vent_CH4->open();
	// wait for 3 seconds
	std::this_thread::sleep_for(std::chrono::seconds(3));
	// close CH4 vent valve
	vent_CH4->close();

	return state_mach.getPreviousState();

}

// ... fn_emergency ... //
b1_states::b1_state b1_states::fn_emergency(b1_states::b1_state new_state) {

	helium_LOX->open();
	helium_CH4->open();
	vent_LOX->open();
	vent_CH4->open();
	pyro_LOX->detonate();
	pyro_CH4->detonate();

	std::cout << "Emergency procedure has been executed.  Draining fuels..." << std::endl;
	return new_state;

}

// ... fn_ERROR ... //
b1_states::b1_state b1_states::fn_ERROR(b1_states::b1_state new_state) {

	std::cout << "ERROR - state machine is not constructed properly" << std::endl;
	return new_state;

}

// ... launch countdown ... //
void b1_states::launch_countdown(void) {

	for (int i = 5; i > -1; i--) {
		std::cout << i << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

}

// ... burnout timer ... //
void b1_states::burnout_timer(void) {
	std::this_thread::sleep_for(std::chrono::seconds(15));
	state_mach.pushEvent(b1_states::b1_event::EV_BURNOUT);
}