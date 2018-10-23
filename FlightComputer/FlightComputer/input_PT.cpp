#include "input_PT.h"

int gather_input() {

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	// TODO: add a check for this
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// TODO: replace this with actual pressure transducer reading code
	int i = 0;
	while (i < 10) {


		if (i == 3 || i == 7) {
			sm.pushEvent(b1_states::EV_NOMINAL);
		}
		if (i == 4 || i == 9) {
			sm.pushEvent(b1_states::EV_OVR_PR);
		}
		if (i == 8) {
			sm.pushEvent(b1_states::EV_FULL_TEMP);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		i++;

	}

	return 0;
	
}