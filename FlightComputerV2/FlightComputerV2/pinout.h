//
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  06 November 2018
// Date Revised:  04 December 2018
// File Name:     pinout.h
// Description:   Constructor file for pinout.cpp.  Defines all the pins and
//                what state they should be exported to.  Also aliases the pin
//                names so they are easily recognizable elsewhere in the code.
//
// GENERAL TODOS
//
// INCLUDES
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
	PIN_SOL_1 = 19,
	PIN_SOL_2 = 5,
	PIN_VENT_1 = 16,
	PIN_VENT_2 = 6,
	PIN_PYRO_1 = 13,
	PIN_PYRO_2 = 20
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