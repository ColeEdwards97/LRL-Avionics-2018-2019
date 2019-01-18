#include "state_machine.h"



state_machine::state_machine() {

	currentState = gs_states::ST_INIT;
	currentEvent = gs_states::EV_NOMINAL;

	is_running = false;

}


// RUN MAIN LOOP
void state_machine::run(void) {

	is_running = true;

	while (currentState != states.ST_TERM) {

		if (!eventQueue.empty()) {

			currentEvent = eventQueue.front();

			for (int i = 0; i < states.transCount(); i++) {

				if (currentState == states.trans[i].st || states.ST_ANY == states.trans[i].st) {

					if (currentEvent == states.trans[i].ev || states.EV_ANY == states.trans[i].ev) {

						currentState = (states.trans[i].fn)(states.trans[i].new_st);
						eventQueue.pop();
						break;

					}

				}

			}

		}

	}
	is_running = false;
}

// GETTERS

std::queue<gs_states::gs_event> state_machine::getEventQueue(void) {
	return eventQueue;
}
gs_states::gs_state state_machine::getCurrentState(void) {
	return currentState;
}
gs_states::gs_event state_machine::getCurrentEvent(void) {
	return currentEvent;
}

// SETTERS

void state_machine::setCurrentState(gs_states::gs_state new_state) {
	currentState = new_state;
}
void state_machine::setCurrentEvent(gs_states::gs_event new_event) {
	currentEvent = new_event;
}

// PUSH EVENT
void state_machine::pushEvent(gs_states::gs_event pushEvent) {
	eventQueue.push(pushEvent);
}

bool state_machine::isRunning(void) {
	return is_running;
}