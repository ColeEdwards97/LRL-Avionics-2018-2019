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
// Date Revised:  25 January 2019
// File Name:     input.h
// Description:   Constructor file for input.cpp.  Defines functions that will
//                be called by threads to recieve various input types
//
// GENERAL TODOS
//
// INCLUDES
#pragma once
#include <wiringPi.h>
#include <iostream>	
#include <fstream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <ads1115.h>
#include "b1_states.h"
#include "state_machine.h"

// METHODS

int gather_PT_input(void);
int gather_user_input(void);