#include "input.h"
#include "b1_states.h"
#include "state_machine.h"

state_machine& input_sm = state_machine::getInstance();
std::unique_lock<std::mutex> lock(input_sm.mtx_isRunning);

// ... Read Pressure Transducer Data ... //
int getPressureTransducerReadings(void) {

	b1_states& states = b1_states::getInstance();

	input_sm.cv_isRunning.wait(lock, [] {return input_sm.isRunning(); });
	//std::cout << "Getting Pressure Transducer Readings..\n";
	logger::info(__FILE__, "Getting Pressure Transducer Readings");
	lock.unlock();

	// DATA FILE FOR LOGGING
	std::ofstream data_file;
	data_file.open("pt_data.txt");
	data_file << "Pressure Transducer Data Log\n";

	// ... adc parameters ... // 
	int pinbase = 100;
	int i2cloc = 0x48;
	int adcbits = 16;
	int chan[2] = { 0,1 };
	int max_val = 750;
	int correction = -89.6604;
	int a2dval;
	float a2dvol;
	float a2dpsi;
	float a2dpsi_correction;
	int max_LOX_pressure = 330;
	int max_CH4_pressure = 330;

	// try to connect to the ADC
	if (ads1115Setup(pinbase, i2cloc) < 0) {
		//std::cout << "Failed setting up I2C device :(\n";
		logger::warn(__FILE__, "Failed setting up I2C device :(");
		return -1;
	}
	else {

		//std::cout << "Reading PT data...\n";

		while (input_sm.isRunning()) {

			for (int j : chan) {

				a2dval = analogRead(pinbase + j);
				a2dvol = a2dval * 4.096 / (pow(2, (adcbits - 1)) - 1);
				a2dpsi = a2dvol * 198.66f - 112.66f + 23 - correction;
				//a2dpsi = a2dval * max_val / (pow(2, (adcbits - 1) - 1)) - correction;

				if (j == 0) {

					std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					data_file << time << "\t" << a2dpsi << "\t";
					printf("LOX Tank Pressure: %f [psi]\n", a2dpsi);
					if (a2dpsi >= max_LOX_pressure) {
						logger::warn(__FILE__, "LOX line is at operating pressure");
						if (!states.vent_LOX->isOpen()) {
							input_sm.pushEvent(states.EV_OVR_PR_LOX);
						}
					}
				}
				if (j == 1) {
					//printf("FUE Tank Pressure: %f [psi]\n", a2dpsi);
					data_file << a2dpsi << "\n";
					if (a2dpsi >= max_CH4_pressure) {
						logger::warn(__FILE__, "CH4 line is at operating pressure");
						if (!states.vent_CH4->isOpen()) {
							input_sm.pushEvent(states.EV_OVR_PR_CH4);
						}
					}

				}

			}

		}

	}
	//std::cout << "Gathered Pressure Transducer Readings\n";
	logger::info(__FILE__, "Gathered Pressure Transducer Readings");
	data_file.close();
	return 0;
}

// ... Read User Input ... //
int getUserInput(void) {

	b1_states& states = b1_states::getInstance();
	
	input_sm.cv_isRunning.wait(lock, [] {return input_sm.isRunning(); });
	//std::cout << "Gathering User Input...\n";
	logger::info(__FILE__, "Gathering User Input");

	int input;
	char confirm;

	while (input_sm.isRunning()) {

		std::cin >> input;
		//input = logger::getIntInput();

		if (static_cast<b1_states::b1_event>(input) == b1_states::EV_LAUNCH) {

			//std::cout << "Are you sure you want to launch? Y/N\n";
			
			prompt:
			logger::info(__FILE__, "Are you sure you want to launch? Y/N");
			std::cin >> confirm;
			//confirm = logger::getCharInput();

			switch (confirm) {
			case 'Y':
				input_sm.pushEvent(static_cast<b1_states::b1_event>(input));
				break;
			case 'y':
				input_sm.pushEvent(static_cast<b1_states::b1_event>(input));
				break;
			case 'N': 
				input_sm.pushEvent(states.EV_CANCEL);
				break;
			case 'n':
				input_sm.pushEvent(states.EV_CANCEL);
				break;
			default:
				goto prompt;
				break;
			}

		}
		else {
			input_sm.pushEvent(static_cast<b1_states::b1_event>(input));
		}

	}
	//std::cout << "Gathered User Input\n";
	logger::info(__FILE__, "Gathered User Input");
	return 0;
}

// ... MAX31855 Set Up ... //
int max31855Setup(const int pinBase, int spiChannel)
{
	struct wiringPiNodeStruct *node;
	if (wiringPiSPISetup(spiChannel, 5000000) < 0)
	//{
	//	logger::info(__FILE__, "MAX31855 Failed to run");
	//}
		return FALSE;

	node = wiringPiNewNode(pinBase, 8); // ... GPIO
	node->fd			= spiChannel;
	//node->analogRead	= myAnalogread;

	return TRUE;
}

//static int myAnalogRead(struct wiringPiNodeStruct *node, int pin)


void check_pt_readings(void) {

	// ... adc parameters ... // 
	int pinbase = 100;
	int i2cloc = 0x48;
	int adcbits = 16;
	int chan[2] = { 0,1 };
	int max_val = 750;
	int correction = -82;
	int a2dval;
	float a2dvol;
	float a2dpsi;
	int max_LOX_pressure = 330;
	int max_CH4_pressure = 330;

	// try to connect to the ADC
	if (ads1115Setup(pinbase, i2cloc) < 0) {
		logger::warn(__FILE__, "Failed setting up I2C device :(");
		return;
	}
	else {

	loop:
		logger::info(__FILE__, "Checking PT readings...");
		for (int i = 1; i <= 100; i++) {

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			for (int j : chan) {

				a2dval = analogRead(pinbase + j);
				a2dvol = a2dval * 4.096 / (pow(2, (adcbits - 1)) - 1);
				a2dpsi = a2dvol * 198.66f - 112.66f + 23;
				//a2dpsi = a2dval * max_val / (pow(2, (adcbits - 1) - 1)) - correction;

				if (j == 0) {
					std::cout << "chan" << j << "\t" << a2dpsi << "\t";
					if (a2dpsi >= max_LOX_pressure) {
						logger::warn(__FILE__, "LOX line is at operating pressure");
					}
				}
				if (j == 1) {
					std::cout << "chan" << j << "\t" << a2dpsi << "\n";
					if (a2dpsi >= max_CH4_pressure) {
						logger::warn(__FILE__, "CH4 line is at operating pressure");
					}

				}

			}

		}
		char check;
		std::cin >> check;
		//check = logger::getCharInput();
		switch (check) {
		case 'Y':
			logger::info(__FILE__, "PT readings look good ;)");
			return;
			break;
		case 'N':
		default:
			goto loop;
			break;
		}

	}

}