#include "tank_level.h"
#include "input.h"
#include "logger.h"
#include "b1_states.h"
#include "b1_hardware.h"
/*
void loadSpiDriver() {
	if (system("gpio load spi") == -1) {
		logger::warn(__FILE__, "Can't load SPI driver: %s\n", strerror(errno));

	}

}
int getThermocoupleReadings(void) {

	// ... Data File for Logging ... //
	std::ofstream data_file_tc;
	data_file_tc << "Thermocouple Data Log \n";

	// ... MAX31855 Parameters ... //
#define MAX31856_WRITE             0x80
#define MAX31856_READ              0x00

#define MAX31856_CR0_REG           0x00
#define MAX31856_CR0_1SHOT         0x40
#define MAX31856_CR0_50HZ          0x01
#define MAX31856_KTYPE             0x03
#define MAX31856_CHIP_SELECT	   0
#define MAX31856_CR0_FAULTCLR      0x02
#define MAX31856_LTCBH_REG         0x0C

	const int spiChannel = 8;
	if (wiringPiSPISetup(spiChannel, 5000000) < 0) {
		logger::info(__FILE__, "SPI Device Failed");
	}
	else {
		uint8_t data[3], Max31856_CR0, Max31856_CR1;
		int temp;

		if (wiringPiSetup() == -1) {
			logger::warn(__FILE__, "Error: wiringPi setup failed.\n");
			return EXIT_FAILURE;
		}
		if (wiringPiSPISetup(MAX31856_CHIP_SELECT, 5000000) < 0) {   // 5MHz - prob 4 on the Pi
			logger::warn(__FILE__, "Error: wiringPi setup failed.\n");
			return EXIT_FAILURE;
		}
		Max31856_CR0 = MAX31856_CR0_50HZ;  // 50 Hz compensation
		Max31856_CR1 = MAX31856_KTYPE; // Thermocouple type

		data[0] = MAX31856_CR0_REG | MAX31856_WRITE;
		data[1] = Max31856_CR0;
		data[2] = Max31856_CR1;

		temp = wiringPiSPIDataRW(MAX31856_CHIP_SELECT, data, 3);
		if (temp == -1) logger::warn(__FILE__, "wiringPiSPIDataRW error %d\n");
		//delay(200);

		//memset(data, 0, 4);
		data[0] = MAX31856_LTCBH_REG | MAX31856_READ;

		if (temp == -1) logger::warn(__FILE__, "wiringPiSPIDataRW error %d\n");
		if (data[3]) logger::warn(__FILE__, "Thermocouple fault\n");
		/*
		while (input_sm.isRunning()) {
			temp = wiringPiSPIDataRW(MAX31856_CHIP_SELECT, data, 107);
			int spi_data = analogRead(8);
			logger::info(__FILE__, std::to_string(temp));
			//logger::info(__FILE__, std::to_string(spi_data));
		}
		

		while (input_sm.isRunning()) {
			temp = data[0] << 16 | data[1] << 8 | data[2];
			if (temp & 0x800000) temp |= 0xFF000000;  // fix sign
			ftemp = 0.0078125 * (double)(temp >> 5);
			logger::info(__FILE__, std::to_string(temp));
			//logger::info(__FILE__, std::to_string(ftemp));
		}
	}
}
*/