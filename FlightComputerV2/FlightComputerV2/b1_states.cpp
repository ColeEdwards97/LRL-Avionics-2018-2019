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
// File Name:     b1_states.cpp
// Description:   Source file for b1_states.h.  Defines the functions to get 
//                and set the state of the Bronco One.
//
// GENERAL TODOS
//
// INCLUDES
#include "b1_states.h"

// CREATE THE B1 HARDWARE
b1_hardware* b1_states::sol_1 = new b1_hardware(PIN_SOL_1, b1_hardware::hardware::SOLENOID);
b1_hardware* b1_states::sol_2 = new b1_hardware(PIN_SOL_2, b1_hardware::hardware::SOLENOID);
b1_hardware* b1_states::vent_1 = new b1_hardware(PIN_VENT_1, b1_hardware::hardware::VENT);
b1_hardware* b1_states::vent_2 = new b1_hardware(PIN_VENT_2, b1_hardware::hardware::VENT);
b1_hardware* b1_states::pyro_1 = new b1_hardware(PIN_PYRO_1, b1_hardware::hardware::PYRO);
b1_hardware* b1_states::pyro_2 = new b1_hardware(PIN_PYRO_2, b1_hardware::hardware::PYRO);

// CONSTRUCTOR
b1_states::b1_states() {

}

// GETTERS

// SETTERS

// METHODS
int b1_states::transCount(void) {
	return (sizeof(trans) / sizeof(*trans));
}

// B1 STATE FUNCTIONS

// ... fn_init2idle ... //
b1_states::b1_state b1_states::fn_init2idle(b1_states::b1_state new_state) {

	sol_1->setSolState(b1_hardware::sol_state::CLOSED);
	sol_2->setSolState(b1_hardware::sol_state::CLOSED);
	vent_1->setVentState(b1_hardware::vent_state::CLOSED);
	vent_2->setVentState(b1_hardware::vent_state::CLOSED);
	pyro_1->setPyroState(b1_hardware::pyro_state::INTACT);
	pyro_2->setPyroState(b1_hardware::pyro_state::INTACT);

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;
	return new_state;

}

// ... fn_idle2fill ... //
b1_states::b1_state b1_states::fn_idle2fill(b1_states::b1_state new_state) {

	vent_1->setVentState(b1_hardware::vent_state::OPEN);
	vent_2->setVentState(b1_hardware::vent_state::OPEN);

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;
	return new_state;

}

// ... fn_fill2pressurize ... //
b1_states::b1_state b1_states::fn_fill2pressurize(b1_states::b1_state new_state) {

	vent_1->setVentState(b1_hardware::vent_state::CLOSED);
	vent_2->setVentState(b1_hardware::vent_state::CLOSED);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	sol_1->setSolState(b1_hardware::sol_state::OPEN);
	sol_2->setSolState(b1_hardware::sol_state::OPEN);

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;
	return new_state;

}

// ... fn_pressurized2ready ... //
b1_states::b1_state b1_states::fn_pressurized2ready(b1_states::b1_state new_state) {

	std::cout << "BRONCO ONE IS READY TO LAUNCH" << std::endl << "WAITING ON YOUR GO..." << std::endl;

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;
	return new_state;

}

// ... fn_ready2launch ... //
b1_states::b1_state b1_states::fn_ready2launch(b1_states::b1_state new_state) {

	pyro_1->setPyroState(b1_hardware::pyro_state::BURST);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	pyro_2->setPyroState(b1_hardware::pyro_state::BURST);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	pyro_1->setPyroState(b1_hardware::pyro_state::INTACT);
	pyro_2->setPyroState(b1_hardware::pyro_state::INTACT);

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;

	return new_state;

}

// ... fn_launch2cruise ... //
b1_states::b1_state b1_states::fn_launch2cruise(b1_states::b1_state new_state) {

	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;

	return new_state;

}

// ... fn_cruise2term ... //
b1_states::b1_state b1_states::fn_cruise2term(b1_states::b1_state new_state) {

	sol_1->setSolState(b1_hardware::sol_state::OPEN);
	sol_2->setSolState(b1_hardware::sol_state::OPEN);
	vent_1->setVentState(b1_hardware::vent_state::OPEN);
	vent_2->setVentState(b1_hardware::vent_state::OPEN);

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;

	return new_state;

}

// ... fn_hold ... //
b1_states::b1_state b1_states::fn_hold(b1_states::b1_state new_state) {

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;

	return new_state;

}

// ... fn_vent ... //
b1_states::b1_state b1_states::fn_vent(b1_states::b1_state new_state) {

	// OPEN VENT VALVES
	vent_1->setVentState(b1_hardware::vent_state::OPEN);
	vent_2->setVentState(b1_hardware::vent_state::OPEN);
	// WAIT for 3 seconds
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	// CLOSE VENT VALVES
	vent_1->setVentState(b1_hardware::vent_state::CLOSED);
	vent_2->setVentState(b1_hardware::vent_state::CLOSED);

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;

	return new_state;

}

// ... fn_emergency ... //
b1_states::b1_state b1_states::fn_emergency(b1_states::b1_state new_state) {

	sol_1->setSolState(b1_hardware::sol_state::OPEN);
	sol_2->setSolState(b1_hardware::sol_state::OPEN);
	vent_1->setVentState(b1_hardware::vent_state::OPEN);
	vent_2->setVentState(b1_hardware::vent_state::OPEN);
	pyro_1->setPyroState(b1_hardware::pyro_state::BURST);
	pyro_2->setPyroState(b1_hardware::pyro_state::BURST);

	std::cout << "state: " << static_cast<int>(new_state) << std::endl;

	return new_state;

}