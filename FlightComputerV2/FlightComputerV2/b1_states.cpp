#include "b1_states.h"

// Construct and initialize the B1 states
b1_states::b1_states() {

	currentState = b1_state::ST_INIT;
	currentEvent = b1_event::EV_NOMINAL;

}

// GETTERS
b1_states::b1_state b1_states::getState(void) {
	return currentState;
}
b1_states::b1_event b1_states::getEvent(void) {
	return currentEvent;
}

// SETTERS
void b1_states::setState(b1_state newState) {
	currentState = newState;
}
void b1_states::setEvent(b1_event newEvent) {
	currentEvent = newEvent;
}

// Get the number of transitions
int b1_states::transCount(void) {
	return (sizeof(trans) / sizeof(*trans));
}

// Define the B1 functions
b1_states::b1_state b1_states::fn1(void) {
	std::cout << "ST_TERM\n";
	return ST_TERM;
}
b1_states::b1_state b1_states::fn2(void) {
	std::cout << "ST_CRUISE\n";
	return ST_CRUISE;
}