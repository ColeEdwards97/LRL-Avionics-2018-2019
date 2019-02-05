#include <iostream>	
#include <cstdio>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <wiringPi.h>

#include "input.h"
#include "pinout.h"

int main(void) {

	std::cout << info(__FILE__, "Started Flight Computer V3");

	// Initialize GPIO pins
	initializePins();

	// Create input threads
	std::thread tPressureTransducerData(getPressureTransducerReadings);
	std::thread tUserInput(getUserInput);


	std::this_thread::sleep_for(std::chrono::seconds(3));


	// Join input threads
	tPressureTransducerData.join();
	tUserInput.join();

	// Wait to exit
	std::cin.ignore();

	return 0;
}