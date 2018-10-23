#pragma once
#include <wiringPi.h>
#include <iostream>	
#include <string>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <chrono>
#include "b1_states.h"
#include "state_machine.h"

int gather_input(void);
int gather_PT_input(void);
// int gather_USER_input(void);