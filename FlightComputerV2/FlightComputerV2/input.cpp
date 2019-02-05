//
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  23 October 2018
// Date Revised:  28 January 2019
// File Name:     input.cpp
// Description:   Source file for input.h.  Defines functions that will be
//                called by threads to recieve various input types
//
// GENERAL TODOS
//
// INCLUDES
#include "input.h"


// METHODS

// ... GATHER_PT_INPUT ... //
int gather_PT_input(void) {

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	std::this_thread::sleep_for(std::chrono::seconds(2));
	//std::unique_lock<std::mutex> lock(sm.mtx_isRunning);
	//sm.cv_isRunning.wait(lock);

	// create a file to save data to
	std::ofstream data_file;
	data_file.open("pt_data.txt");
	data_file << "Pressure Transducer Data Log\n";

	// define ADC parameters
	int pinbase = 100;
	int i2cloc = 0x48;
	int adcbits = 16;
	int a2dval;
	float a2dvol;
	float a2dpsi;
	//float vref = 5;
	int max_LOX_pressure = 325;
	int max_CH4_pressure = 330;

	// try to connect to the ADC
	if (ads1115Setup(pinbase, i2cloc) < 0) {
		std::cout << "Failed setting up I2C device :(\n";
		return -1;
	}
	else {

		std::cout << "Gathering pt data...\n";

		int chan[2] = { 0, 1 };

		while(sm.isRunning()) {

			for (int j : chan) {

				a2dval = analogRead(pinbase + j);
				//a2dvol = a2dval * vref / (pow(2, (adcbits - 1)) - 1);
				a2dvol = a2dval * 4.096 / (pow(2, (adcbits - 1)) - 1);
				a2dpsi = a2dvol * 198.66f - 112.66f;

				//std::cout << "chan " << j << " " << a2dpsi << " psi" << std::endl;

				if (j == 0) {

					data_file << "chan " << j << "\t" << a2dpsi << "\t";

					if (a2dpsi >= max_LOX_pressure) {
						std::cout << "LOX line is at operating pressure";
						//if (!sm.isVentingLOX()) {
							sm.pushEvent(b1_states::b1_event::EV_OVR_PR_LOX);
						//}
					}
				}
				if (j == 1) {

					data_file << "chan " << j << "\t" << a2dpsi << "\n";

					if (a2dpsi >= max_CH4_pressure) {
						std::cout << "CH4 line is at operating pressure";
						//if (!sm.isVentingCH4()) {
							sm.pushEvent(b1_states::b1_event::EV_OVR_PR_CH4);
						//}
					}
				}

			}

		}
		data_file.close();
		return 0;
	}

}

// ... GATHER_USER_INPUT ... //
int gather_user_input(void) {

	// get the state machine so we can push events to it
	state_machine& sm = state_machine::getInstance();

	// wait for the state machine to start
	std::this_thread::sleep_for(std::chrono::seconds(2));
	//std::unique_lock<std::mutex> lock(sm.mtx_isRunning);
	//sm.cv_isRunning.wait(lock);

	int input;
	char confirm;

	std::cout << "Gathering user input...\n";

	while (sm.isRunning()) {

		std::cin >> input;

		if (static_cast<b1_states::b1_event>(input) == b1_states::EV_LAUNCH) {

			std::cout << "Are you sure you want to launch? Y/N\n";
			std::cin >> confirm;

			switch (confirm) {
			case 'Y':
				sm.pushEvent(static_cast<b1_states::b1_event>(input));
				break;
			case 'N':
				sm.pushEvent(b1_states::b1_event::EV_CANCEL);
				break;
			default:
				break;
			}

		}
		else {
			sm.pushEvent(static_cast<b1_states::b1_event>(input));
		}

	}
	return 0;
}