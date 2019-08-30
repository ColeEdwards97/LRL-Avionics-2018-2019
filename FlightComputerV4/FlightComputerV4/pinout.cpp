#include "pinout.h"


// STRUCTS
static pins pin_init[8] = {
	{ PIN_HELIUM_LOX,  OUTPUT, HIGH },
	{ PIN_HELIUM_CH4,  OUTPUT, HIGH },
	{ PIN_VENT_LOX, OUTPUT, HIGH },
	{ PIN_VENT_CH4, OUTPUT, HIGH },
	{ PIN_PYRO_LOX, OUTPUT, HIGH },
	{ PIN_PYRO_CH4, OUTPUT, HIGH },
	{ PIN_BAT_5V, OUTPUT, HIGH },
	{ PIN_BAT_24V, OUTPUT, HIGH }
};

// METHODS

// ... Initialize GPIO pins to initial states ... //
int initializePins() {

	//std::cout << "Exporting GPIO pins...\n";
	logger::info(__FILE__, "Exporting GPIO pins...");

	wiringPiSetupGpio();

	int i;
	for (i = 0; i < countPins(); i++) {
		pinMode(pin_init[i].pin, pin_init[i].mode);	// initialize the pins with the corresponding pin mode
		digitalWrite(pin_init[i].pin, pin_init[i].state); // set the default state of the pin
	}

	//std::cout << "GPIO pins exported successfully\n";
	logger::info(__FILE__, "GPIO pins exported successfully");
	return 0;

}

// ... Cleanup GPIO pins before shutting down ... //
int cleanupPins(void) {

	int i;
	for (i = 0; i < countPins(); i++) {

		digitalWrite(pin_init[i].pin, LOW);
		// TODO: this will return all hardware to their idle state... should we do this?
	}

	return 0;

}

// ... Count the number of pin configurations to set ... //
int countPins(void) {
	return (sizeof(pin_init) / sizeof(*pin_init));
}