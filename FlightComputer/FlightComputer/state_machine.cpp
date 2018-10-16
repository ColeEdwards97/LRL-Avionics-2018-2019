#include "state_machine.h"


// CONSTRUCTOR
state_machine::state_machine() {

	// state machine initialization
	eventQueue.push(b1_states::EV_OVR_PR); // TODO: remove later; integrate into push system

}

// RUN MAIN LOOP
void state_machine::run(void) {


	// main loop code
	std::cout << "starting state machine...\n";

	// initialized values
	int i;
	int state = states.getState();
	int event = states.getEvent();

	// while currentState != ST_TERM
	//		while !eventQueue.empty()
	//			if state == currentstate or state == any state
	//				if event == currentevent or event == any event
	//					change the state

	while (state != states.ST_TERM) {

		while (!eventQueue.empty()) {

			std::cout << "Queue has members has " << eventQueue.size() << " member(s)!\n";

			event = eventQueue.front();

			for (i = 0; i < states.transCount(); i++) {

				if ((state == states.trans[i].st) || (states.ST_ANY == states.trans[i].st)) {

					if ((event == states.trans[i].ev) || (states.EV_ANY == states.trans[i].ev)) {
						state = (states.trans[i].fn)();
						eventQueue.pop();
						break;
					}

				}

			}

		}

	}

}

// GETTERS
std::queue<b1_states::b1_event> state_machine::getEventQueue(void) {
	return eventQueue;
}
