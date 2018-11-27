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
// Date Revised:  26 November 2018
// File Name:     main.cpp
// Description:   The main file.  Everything on the Flight Computer is called
//                from this file.  It initializes the Flight Computer and
//                delegates tasks to various other files.  This code utilizes 
//                multi-threading which allows the flight computer to run while
//                at the same time, collecting input from various sources.  The
//                Flight Computer can then be updated in real time allowing 
//                multiple tasks to run simultaneously.
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
//	// data collection should be run in a separate thread(s)
//	// this function should just pull the latest value from the thread
int main() {

	initialize_pins();

	std::cout << "[INFO][main.cpp] Starting Flight Computer" << std::endl;

	// start the thread(s) that gathers system inputs
	std::thread th_INPUT(gather_input);
	std::thread th_USER_INPUT(gather_user_input);

	// run the finite state machine
	sm.run();

	// wait until input thread(s) finishes
	th_INPUT.join();
	th_USER_INPUT.join();

	// stop program and wait for input
	int i;
	std::cout << "waiting to end program..." << std::endl;
	std::cin >> i;
	
	// cleanup the gpio pins
	cleanup();

	return 0;

}