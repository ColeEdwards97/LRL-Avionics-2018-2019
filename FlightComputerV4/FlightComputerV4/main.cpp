#include <iostream>	
#include <cstdio>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <wiringPi.h>

#include "state_machine.h"
#include "input.h"
#include "logger.h"


int main(void) {
	
	logger::info(__FILE__, "Started Flight Computer");

	// Initialize State Machine
	state_machine& sm = state_machine::getInstance();

	// Initialize GPIO pins k
	initializePins();

	// Create input threads
	//std::thread tPressureTransducerData(getPressureTransducerReadings);
	std::thread tUserInput(getUserInput);

	// Start the state machine
	// To change the time interval for how long Pyro valve will open
	// CHANGING IN "pyrovalve.h" -> pyroCutOffDelaysMS -> Change time in micro-second scale

	sm.run();

	// Join input threads
	//tPressureTransducerData.join();
	tUserInput.join();

	// Wait to exit
	std::cin.ignore();
	std::cin.ignore();

	cleanupPins();

	return 0;
}