#pragma once
#include "b1_hardware.h"
#include <thread>
#include <chrono>


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

	int pyroCutOffDelayMS = 500;

};