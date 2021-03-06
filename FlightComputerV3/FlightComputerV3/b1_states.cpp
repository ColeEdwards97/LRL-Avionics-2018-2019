#include "b1_states.h"
#include "state_machine.h"


// CREATE HARDWARE
solenoid* b1_states::helium_LOX = new solenoid(PIN_HELIUM_LOX, solenoid::solenoidType::NC, solenoid::solenoidState::CLOSED, solenoid::solenoidLine::LOX);
solenoid* b1_states::helium_CH4 = new solenoid(PIN_HELIUM_CH4, solenoid::solenoidType::NC, solenoid::solenoidState::CLOSED, solenoid::solenoidLine::CH4);
solenoid* b1_states::vent_LOX = new solenoid(PIN_VENT_LOX, solenoid::solenoidType::NC, solenoid::solenoidState::CLOSED, solenoid::solenoidLine::LOX);
solenoid* b1_states::vent_CH4 = new solenoid(PIN_VENT_CH4, solenoid::solenoidType::NO, solenoid::solenoidState::CLOSED, solenoid::solenoidLine::CH4);
pyrovalve* b1_states::pyro_LOX = new pyrovalve(PIN_PYRO_LOX, pyrovalve::pyroType::NC);
pyrovalve* b1_states::pyro_CH4 = new pyrovalve(PIN_PYRO_CH4, pyrovalve::pyroType::NC);


// GET INSTANCE OF STATE MACHINE
state_machine& sm_st = state_machine::getInstance();


// CONSTRUCTOR
b1_states::b1_states() {
}


// STATE FUNCTIONS

// ... fn_init_init ... //
b1_states::b1_state b1_states::fn_init_init(b1_states::b1_state nextState) {
	logger::info(__FILE__, "State Machine started successfully. All valves in their unpowered states");
	return nextState;
}


// ... fn_init_idle ... //
b1_states::b1_state b1_states::fn_init_idle(b1_states::b1_state nextState) {
	
	helium_LOX->close();
	helium_CH4->close();

	vent_LOX->close();
	vent_CH4->close();

	logger::info(__FILE__, "Helium Valves closed. Vent Valves closed.");
	return nextState;
}

// ... fn_idle_fill ... //
b1_states::b1_state b1_states::fn_idle_fill(b1_states::b1_state nextState) {

	vent_LOX->open();
	vent_CH4->open();
	
	logger::info(__FILE__, "Helium Valves Closed. Vent Valves open.");
	logger::info(__FILE__, "Begin Filling Sequence.");
	return nextState;
}

// ... fn_fill_pressurize ... //
b1_states::b1_state b1_states::fn_fill_pressurize(b1_states::b1_state nextState) {
	
	helium_LOX->open();
	helium_CH4->open();

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	vent_LOX->close();
	vent_CH4->close();

	//std::cout << "Bronco One is being pressurized...\nContinue when pressurization is finished\n";
	logger::info(__FILE__, "Bronco One is being pressurized...");
	logger::info(__FILE__, "Continue when pressurization is finished.");
	return nextState;
}

// ... fn_pressurize_pressurized ... //
b1_states::b1_state b1_states::fn_pressurize_pressurized(b1_states::b1_state nextState) {
	//std::cout << "Bronco One is pressurized and ready to launch\nWaiting on your go...\n";
	logger::info(__FILE__, "Bronco One is pressurized and ready to launch.");
	logger::info(__FILE__, "Waiting on your go...");
	return nextState;
}

// ... fn_pressurized_launch ... //
b1_states::b1_state b1_states::fn_pressurized_launch(b1_states::b1_state nextState) {

	launch_countdown();

	pyro_CH4->detonate();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	pyro_LOX->detonate();

	std::thread(burnout_timer).detach();

	return nextState;
}

// ... fn_launch_term ... //
b1_states::b1_state b1_states::fn_launch_term(b1_states::b1_state nextState) {

	helium_LOX->open();
	helium_CH4->open();
	vent_LOX->open();
	vent_CH4->open();

	//std::cout << "Bronco One has successfully launched...\n";
	//std::cout << "Good luck on recovery :)\n";
	logger::info(__FILE__, "Bronco One has successfully launched!");
	logger::info(__FILE__, "Good luck on recovery :)");
	return nextState;
}

// ... fn_vent_LOX ... //
b1_states::b1_state b1_states::fn_vent_LOX(b1_states::b1_state nextState) {

	//std::cout << "Venting LOX line\n";
	logger::info(__FILE__, "Venting LOX line");
	std::thread(vent_LOX_pressure).detach();
	return sm_st.getPreviousState();

}

// ... fn_vent_CH4 ... //
b1_states::b1_state b1_states::fn_vent_CH4(b1_states::b1_state nextState) {

	//std::cout << "Venting CH4 line\n";
	logger::info(__FILE__, "Venting CH4 line");
	std::thread(vent_CH4_pressure).detach();
	return sm_st.getPreviousState();

}

// ... fn_EMERGENCY ... //
b1_states::b1_state b1_states::fn_EMERGENCY(b1_states::b1_state nextState) {

	//std::cout << "Emergency procedure has been executed. Draining fuel lines...\n";
	logger::info(__FILE__, "Emergency procedure has been executed. Draining fuel lines");
	drain_lines();
	return nextState;
}

// ... fn_CANCEL ... //
b1_states::b1_state b1_states::fn_CANCEL(b1_states::b1_state nextState) {

	vent_CH4->open();
	vent_LOX->open();

	helium_CH4->close();
	helium_LOX->close();

	//std::cout << "Launch has been cancelled\n";
	//std::cout << "Bronco One is being depressurized...\n";
	//std::cout << "Press ENTER to continue\n";
	logger::info(__FILE__, "Launch has been cancelled");
	logger::info(__FILE__, "Bronco One is being depressurized...");
	logger::info(__FILE__, "Press ENTER to continue");
	std::cin.ignore();
	std::cin.ignore();

	// Try pressurizing again or drain the lines
	char mode;
	//std::cout << "R: return to pressurization state\nD: drain lines\n";

prompt:
	logger::info(__FILE__, "R: return to pressurization state");
	logger::info(__FILE__, "D: drain lines");
	std::cin >> mode;

	switch (mode) {
	case 'R':
		//std::cout << "Returning to pressurization state\n";
		//std::cout << "Enter 3 to pressurize\n";
		logger::info(__FILE__, "Returning to pressurization state. Enter 3 to pressurize");
		return ST_FILL;
	case 'D':
		//std::cout << "Executing drain procedure\n";
		logger::info(__FILE__, "Executing drain procedure");
		drain_lines();
		return ST_TERM;
	default:
		goto prompt;
		break;
	}
	return nextState;
}

// ... fn_ERROR ... //
b1_states::b1_state b1_states::fn_ERROR(b1_states::b1_state nextState) {
	//std::cout << "State Machine not constructed properly. Check transition table.\n";
	logger::warn(__FILE__, "State Machine transition table not constructed properly");
	return sm_st.getPreviousState();
}

// METHODS

// ... count the number of transitions ... //
int b1_states::transCount(void) {
	return (sizeof(trans) / sizeof(*trans));
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

	//std::cout << "Bronco One is launching in...\n";
	logger::info(__FILE__, "Bronco One is launching in NOW...");

	//for (int i = 5; i > -1; i--) {
		//std::cout << i << "\n";
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	//}

}

// ... burnout timer ... //
void b1_states::burnout_timer(void) {
	std::this_thread::sleep_for(std::chrono::minutes(1));
	sm_st.pushEvent(b1_states::b1_event::EV_BURNOUT);
}

// ... drain lines ... //
void b1_states::drain_lines(void) {

	std::this_thread::sleep_for(std::chrono::seconds(10));

	//std::cout << "Draining LOX line\n";
	logger::info(__FILE__, "Draining LOX line");
	helium_CH4->close();
	vent_CH4->open();
	vent_LOX->close();
	helium_LOX->open();
	pyro_LOX->detonate();

	std::this_thread::sleep_for(std::chrono::minutes(5));

	//std::cout << "Press 'ENTER' to proceed with draining CH4 line\n";
	logger::info(__FILE__, "Press ENTER to proceed with draining CH4 line");
	std::cin.ignore();
	std::cin.ignore();

	//std::cout << "Draining CH4 line...\n";
	logger::info(__FILE__, "Draining CH4 line");
	vent_LOX->open();
	vent_CH4->close();
	helium_CH4->open();
	pyro_CH4->detonate();

	std::this_thread::sleep_for(std::chrono::minutes(5));

	vent_CH4->open();
	//std::cout << "Fuel lines drained successfully\n";
	logger::info(__FILE__, "Fuel lines drained successfully");

}