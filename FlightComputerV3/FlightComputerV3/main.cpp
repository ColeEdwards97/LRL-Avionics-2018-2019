#include <iostream>	
#include <cstdio>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <wiringPi.h>

#include "state_machine.h"
#include "input.h"


// Initialize State Machine
state_machine& sm = state_machine::getInstance();

int main(void) {
	
	std::cout << "Started Flight Computer\n";

	// Initialize GPIO pins
	initializePins();

	// Create input threads
	std::thread tPressureTransducerData(getPressureTransducerReadings);
	std::thread tUserInput(getUserInput);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	// Start the state machine
	sm.run();

	// Join input threads
	tPressureTransducerData.join();
	tUserInput.join();

	// Wait to exit
	std::cin.ignore();

	return 0;
}