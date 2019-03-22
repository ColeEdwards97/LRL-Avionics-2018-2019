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
// Date Revised:  28 January 2019
// File Name:     b1_states.cpp
// Description:   Source file for b1_states.h.  Defines the functions to get 
//                and set the state of the Bronco One.
//
// GENERAL TODOS
//
// INCLUDES
#include "b1_states.h"
#include "state_machine.h"

// CREATE THE B1 HARDWARE
solenoid* b1_states::helium_LOX = new solenoid(PIN_HELIUM_LOX, solenoid::NC, solenoid::CLOSED, solenoid::HELIUM, solenoid::LOX);
solenoid* b1_states::helium_CH4 = new solenoid(PIN_HELIUM_CH4, solenoid::NC, solenoid::CLOSED, solenoid::HELIUM, solenoid::CH4);
solenoid* b1_states::vent_LOX = new solenoid(PIN_VENT_LOX, solenoid::NC, solenoid::CLOSED, solenoid::VENT, solenoid::LOX);
solenoid* b1_states::vent_CH4 = new solenoid(PIN_VENT_CH4, solenoid::NO, solenoid::CLOSED, solenoid::VENT, solenoid::CH4);
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

	std::cout << "State Machine started successfully\n";
	std::cout << "All valves in their idle states\n";

	return new_state;

}

// ... fn_init2idle ... //
b1_states::b1_state b1_states::fn_init2idle(b1_states::b1_state new_state) {

	helium_LOX->close();
	helium_CH4->close();
	vent_LOX->close();
	vent_CH4->close();

	std::cout << "Bronco One has been initialized...\n";
	std::cout << "Helium and Vent valves closed\n";
	return new_state;

}

// ... fn_idle2fill ... //
b1_states::b1_state b1_states::fn_idle2fill(b1_states::b1_state new_state) {

	vent_LOX->open(); 
	vent_CH4->open();

	std::cout << "Vent valves open\n";
	std::cout << "Bronco One is ready to be filled\n";
	std::cout << "Begin filling sequence\n";
	return new_state;

}

// ... fn_fill2pressurize ... //
b1_states::b1_state b1_states::fn_fill2pressurize(b1_states::b1_state new_state) {

	helium_LOX->open();
	helium_CH4->open();

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	vent_LOX->close();
	vent_CH4->close();

	std::cout << "Bronco One is being pressurized...\n";
	std::cout << "Continue when pressurization is finished\n";
	return new_state;

}

// ... fn_pressurized2ready ... //
b1_states::b1_state b1_states::fn_pressurized2ready(b1_states::b1_state new_state) {

	std::cout << "Bronco One is pressurized and ready to launch\n";
	std::cout << "Waiting on your go...\n";
	return new_state;

}

// ... fn_ready2launch ... //
b1_states::b1_state b1_states::fn_ready2launch(b1_states::b1_state new_state) {
	
	launch_countdown();

	pyro_CH4->detonate();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	pyro_LOX->detonate();

	std::thread(burnout_timer).detach();

	return new_state;

}

// ... fn_launch2term ... //
b1_states::b1_state b1_states::fn_launch2term(b1_states::b1_state new_state) {

	helium_LOX->open();
	helium_CH4->open();
	vent_LOX->open();
	vent_CH4->open();

	std::cout << "Bronco One has successfully launched...\n";
	std::cout << "Good luck on recovery :)\n";

	return new_state;

}

// ... fn_vent_LOX ... //
b1_states::b1_state b1_states::fn_vent_LOX(b1_states::b1_state new_state) {

	std::cout << "Venting LOX line\n";

	std::thread(vent_LOX_pressure).detach();

	return state_mach.getPreviousState();

}

// ... fn_vent_CH4 ... //
b1_states::b1_state b1_states::fn_vent_CH4(b1_states::b1_state new_state) {

	std::cout << "Venting CH4 line\n";

	std::thread(vent_CH4_pressure).detach();
	

	return state_mach.getPreviousState();

}

// ... fn_emergency ... //
b1_states::b1_state b1_states::fn_emergency(b1_states::b1_state new_state) {

	std::cout << "Emergency procedure has been executed. Draining fuel lines...\n";

	drain_lines();

	return new_state;

}

// ... fn_cancel ... //
b1_states::b1_state b1_states::fn_cancel(b1_states::b1_state new_state) {

	vent_CH4->open();
	vent_LOX->open();

	helium_CH4->close();
	helium_LOX->close();

	std::cout << "Launch has been cancelled\n";
	std::cout << "Bronco One is being depressurized...\n";
	std::cout << "Press ENTER to continue\n";
	std::cin.ignore();
	std::cin.ignore();

	// Try pressurizing again or drain the lines
	char mode;
	std::cout << "R: return to pressurization state\nD: drain lines\n";
	std::cin >> mode;

	switch (mode) {
	case 'R':
		std::cout << "Returning to pressurization state\n";
		std::cout << "Enter 3 to pressurize\n";
		return ST_FILL;
	case 'D':
		std::cout << "Executing drain procedure\n";
		drain_lines();
		return ST_TERM;
	default:
		break;
	}
	
	return new_state;

}

// ... fn_ERROR ... //
b1_states::b1_state b1_states::fn_ERROR(b1_states::b1_state new_state) {

	std::cout << "ERROR - state machine is not constructed properly\n";
	return new_state;

}

// ... vent_LOX - to be spawned in a thread to prevent backing up the state machine ... //
void b1_states::vent_LOX_pressure(void) {

	// open LOX vent valve
	// wait for 3 seconds
	// close LOX vent valve

	vent_LOX->open();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	vent_LOX->close();

}

// ... vent_CH4 - to be spawned in a thread to prevent backing up the state machine ... //
void b1_states::vent_CH4_pressure(void) {

	// open CH4 vent valve
	// wait for 3 seconds
	// close CH4 vent valve

	vent_CH4->open();
	std::this_thread::sleep_for(std::chrono::milliseconds(250));
	vent_CH4->close();

}

// ... launch countdown ... //
void b1_states::launch_countdown(void) {

	std::cout << "Bronco One is launching!...\n";

	//for (int i = 5; i > 0; i--) {
		//std::cout << i << "\n";
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	//}

}

// ... burnout timer ... //
void b1_states::burnout_timer(void) {
	std::this_thread::sleep_for(std::chrono::minutes(1));
	state_mach.pushEvent(b1_states::b1_event::EV_BURNOUT);
}

// ... drain lines ... //
void b1_states::drain_lines(void) {

	std::cout << "Draining LOX line\n";
	helium_CH4->close();
	vent_CH4->open();
	vent_LOX->close();
	helium_LOX->open();
	pyro_LOX->detonate();

	std::this_thread::sleep_for(std::chrono::minutes(5));

	std::cout << "Press 'ENTER' to proceed with draining CH4 line\n";
	std::cin.ignore();
	std::cin.ignore();

	std::cout << "Draining CH4 line...\n";
	vent_LOX->open();
	vent_CH4->close();
	helium_CH4->open();
	pyro_CH4->detonate();

	std::this_thread::sleep_for(std::chrono::minutes(5));

	vent_CH4->open();
	std::cout << "Fuel lines drained successfully\n";

}