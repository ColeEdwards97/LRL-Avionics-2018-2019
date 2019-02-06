#include "input.h"
#include "b1_states.h"
#include "state_machine.h"

state_machine& input_sm = state_machine::getInstance();
std::unique_lock<std::mutex> lock(input_sm.mtx_isRunning);

// ... Read Pressure Transducer Data ... //
int getPressureTransducerReadings(void) {

	b1_states& states = b1_states::getInstance();

	input_sm.cv_isRunning.wait(lock, [] {return input_sm.isRunning(); });
	std::cout << "Getting Pressure Transducer Readings..\n";
	lock.unlock();

	// DATA FILE FOR LOGGING
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
	int max_LOX_pressure = 325;
	int max_CH4_pressure = 330;

	// try to connect to the ADC
	if (ads1115Setup(pinbase, i2cloc) < 0) {
		std::cout << "Failed setting up I2C device :(\n";
		return -1;
	}
	else {

		std::cout << "Reading PT data...\n";

		int chan[2] = { 0,1 };

		while (input_sm.isRunning()) {

			for (int j : chan) {

				a2dval = analogRead(pinbase + j);
				a2dvol = a2dval * 4.096 / (pow(2, (adcbits - 1)) - 1);
				a2dpsi = a2dvol * 198.66f - 112.66f;

				if (j == 0) {

					std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					data_file << time << "\t" << a2dpsi << "\t";

					if (a2dpsi >= max_LOX_pressure) {
						std::cout << "LOX line is at operating pressure";
						if (!states.vent_LOX->isOpen()) {
							input_sm.pushEvent(states.EV_OVR_PR_LOX);
						}
					}

				}
				if (j == 1) {

					data_file << a2dpsi << "\n";

					if (a2dpsi >= max_CH4_pressure) {
						std::cout << "CH4 line is at operating pressure";
						if (!states.vent_CH4->isOpen()) {
							input_sm.pushEvent(states.EV_OVR_PR_CH4);
						}
					}

				}

			}

		}

	}

	std::cout << "Gathered Pressure Transducer Readings\n";
	data_file.close();
	return 0;

}

// ... Read User Input ... //
int getUserInput(void) {

	b1_states& states = b1_states::getInstance();
	
	input_sm.cv_isRunning.wait(lock, [] {return input_sm.isRunning(); });
	std::cout << "Gathering User Input...\n";

	int input;
	char confirm;

	while (input_sm.isRunning()) {

		std::cin >> input;

		if (static_cast<b1_states::b1_event>(input) == b1_states::EV_LAUNCH) {

			std::cout << "Are you sure you want to launch? Y/N\n";
			std::cin >> confirm;

			switch (confirm) {
			case 'Y':
				input_sm.pushEvent(static_cast<b1_states::b1_event>(input));
				break;
			case 'N':
				input_sm.pushEvent(states.EV_EMERG);
				break;
			default:
				break;
			}

		}
		else {
			input_sm.pushEvent(static_cast<b1_states::b1_event>(input));
		}

	}
	std::cout << "Gathered User Input\n";
	return 0;
}