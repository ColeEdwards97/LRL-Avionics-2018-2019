#include "state_machine.h"
#include "b1_states.h"


// CONSTRUCTOR
state_machine::state_machine() {

}

// MAIN LOOP
void state_machine::run(void) {

	// while currentState != ST_TERM
	//		while !eventQueue.empty()
	//			if state == currentstate or state == any state
	//				if event == currentevent or event == any event
	//					change the state


}

// METHODS
void state_machine::pushEvent(b1_states::b1_event ev) {
	eventQueue.push(ev);
}
bool state_machine::isRunning(void) {
	return bisRunning;
}

// GETTERS
std::queue<b1_states::b1_event> state_machine::getEventQueue(void) {
	return eventQueue;
}
b1_states::b1_state state_machine::getCurrentState(void) {
	return currentState;
}

b1_states::b1_event state_machine::getCurrentEvent(void) {
	return currentEvent;
}

b1_states::b1_state state_machine::getPreviousState(void) {
	return previousState;
}

// SETTERS
void state_machine::setCurrentState(b1_states::b1_state st) {
	currentState = st;
}

void state_machine::setCurrentEvent(b1_states::b1_event ev) {
	currentEvent = ev;
}
