#include "state_machine.h"


// CONSTRUCTOR
state_machine::state_machine() {

	// state machine initialization

}

// RUN MAIN LOOP
void state_machine::run(void) {

	// main loop code
	std::cout << "starting state machine...\n";

	// initialized values
	int i;
	b1_states::b1_state state = states.getState();
	b1_states::b1_event event = states.getEvent();

	// while currentState != ST_TERM
	//		while !eventQueue.empty()
	//			if state == currentstate or state == any state
	//				if event == currentevent or event == any event
	//					change the state

	std::cout << "status: " << std::endl;
	std::cout << "-state: " << static_cast<int>(state) << std::endl;
	std::cout << "-event: " << static_cast<int>(event) << std::endl;

	while (state != states.ST_TERM) {

		if (!eventQueue.empty()) {

			std::cout << "Queue has " << eventQueue.size() << " member(s)!\n";
			event = eventQueue.front();

			// update the status variable - only for data collection
			//b1_status::currentState = state;
			//b1_status::lastEvent = event;
			// results in errors

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
};
state_machine::b1_status state_machine::getCurrentStatus(void) {
	state_machine::b1_status status;
	return status;
};

// METHODS
void state_machine::pushEvent(b1_states::b1_event pushEvent) {
	eventQueue.push(pushEvent);
};