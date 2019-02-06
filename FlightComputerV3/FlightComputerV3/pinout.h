#pragma once
#include <iostream>
#include <string>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>
#include <wiringSerial.h>
#include <wiringShift.h>

#include "logger.h"


// ENUMS
enum PIN_ALIAS {
	PIN_HELIUM_LOX = 5,
	PIN_HELIUM_CH4 = 13,
	PIN_VENT_LOX = 6,
	PIN_VENT_CH4 = 19,
	PIN_PYRO_LOX = 12,
	PIN_PYRO_CH4 = 16
};

// STRUCTS
typedef struct {
	int pin;	// BCM Pin
	int mode;	// 0:input, 1:output
	int state;  // 0:LOW, 1:HIGH
} pins;

// METHODS
int countPins(void);
int initializePins(void);
int cleanupPins(void);