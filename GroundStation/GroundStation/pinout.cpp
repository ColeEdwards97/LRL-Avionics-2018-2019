#include "pinout.h"


// STRUCTS
static pins pin_init[4] = {
	{ PIN_LINACT_LOX,  OUTPUT, HIGH },
	{ PIN_LINACT_CH4,  OUTPUT, HIGH },
	{ PIN_VALVE_LOX, OUTPUT, HIGH },
	{ PIN_VALVE_CH4, OUTPUT, HIGH }
};

// METHODS
// initialize pins
int initialize_pins() {

	std::cout << "exporting pins" << std::endl;

	wiringPiSetupGpio();

	for (int i = 0; i < pin_count(); i++) {

		pinMode(pin_init[i].pin, pin_init[i].mode);	// initialize the pins with the corresponding pin mode
		digitalWrite(pin_init[i].pin, pin_init[i].state); // set the default state of the pin

	}

	return 0;

}

// cleanup pins
int cleanup(void) {

	for (int i = 0; i < pin_count(); i++) {
		digitalWrite(pin_init[i].pin, LOW);
	}

	return 0;

}

// Count the number of pin configurations to set
int pin_count(void) {
	return (sizeof(pin_init) / sizeof(*pin_init));
}