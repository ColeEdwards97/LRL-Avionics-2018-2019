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
#include <ctime>
#include <condition_variable>
#include <ads1115.h>

#include "logger.h"


// Forward Declaration
class b1_states;
class state_machine;

// METHODS
int getPressureTransducerReadings(void);
int getUserInput(void);