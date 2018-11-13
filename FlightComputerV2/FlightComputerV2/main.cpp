//
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards, Mark Murphy
// Date Created:  23 October 2018
// Date Revised:  13 November 2018
// File Name:     main.cpp
// Description:   The main file.  Everything on the Flight Computer is called
//                from this file.  It initializes the Flight Computer and
//                delegates tasks to various other files.  This code utilizes 
//                multi-threading which allows the flight computer to run while
//                at the same time, collecting input from various sources.  The
//                Flight Computer can then be updated in real time allowing 
//                multiple tasks to run simultaneously.
//
//
// GENERAL TODOS
// TODO: write proper initialization code w/ error handling
//
// INCLUDES
#include <wiringPi.h>
#include <iostream>	
#include <string>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>
#include "state_machine.h"
#include "input.h"

// INSTANCE THE STATE MACHINE
state_machine& sm = state_machine::getInstance();

// TODO: create threads for input
// TODO: add code to gather output from users and hardware
//	// some list of inputs to get based on importance
//	// data collection should be run in a separate thread
//	// this function should just pull the latest value from the thread
//	// ***consider having another thread notify this thread of a change in event
int main() {

	initialize_pins();

	// CODE FOR TESTING
	//std::cout << "test flash" << std::endl;
	//wiringPiSetupSys();
	//wiringPiSetupGpio();
	//wiringPiSetupSys();
	//
	//pinMode(LED, OUTPUT);
	//
	//digitalWrite(LED, HIGH);  // On
	//delay(500); // ms
	//digitalWrite(LED, LOW);	  // Off
	//delay(500);
	// End of testing code


	std::cout << "[INFO][main.cpp] Starting Flight Computer" << std::endl;

	// start the thread that gathers system inputs
	std::thread th_INPUT(gather_input);

	// run the finite state machine
	// add a return in state machine for status
	// while(status)...
	sm.run();

	// wait until input thread finishes
	th_INPUT.join();

	int i;
	std::cin >> i;

	cleanup();

	return 0;

}