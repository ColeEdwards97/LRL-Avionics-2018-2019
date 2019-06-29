#pragma once
#include "b1_hardware.h"
#include <thread>
#include <chrono>

// If the design changes from Pyro Valve to Servo Actuator Valve
// Just change Delay time at line 39 to properly open specific valve.
class pyrovalve : public b1_hardware {

public:

	// ENUMS
	enum pyroType {
		NO = 0,
		NC = 1
	};
	enum pyroState {
		OPEN = 0,
		CLOSED = 1
	};

	// CONSTRUCTORS
	pyrovalve(int, pyroType);

	// METHODS
	void initialize(void);
	void detonate(void);
	static void cutPower(int, int);

	pyroType getPyroType(void);
	pyroState getCurrentState(void);

private:

	// VARIABLES
	pyroType type;
	pyroState state;

	int pyroCutOffDelayMS = 5000;

};