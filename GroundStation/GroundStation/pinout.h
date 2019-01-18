#pragma once
#ifndef PINOUT_H
#define PINOUT_H

#include <iostream>
#include <string>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringPiSPI.h>
#include <wiringSerial.h>
#include <wiringShift.h>

// ENUMS
enum PIN_ALIAS {
	PIN_LINACT_LOX = 1,
	PIN_LINACT_CH4 = 2,
	PIN_VALVE_LOX = 3,
	PIN_VALVE_CH4 = 4
};

// STRUCTS
typedef struct {
	int pin;	// BCM Pin
	int mode;	// 0:input, 1:output
	int state;  // 0:LOW, 1:HIGH
} pins;

// METHODS
int pin_count(void);
int initialize_pins(void);
int cleanup(void);

#endif

