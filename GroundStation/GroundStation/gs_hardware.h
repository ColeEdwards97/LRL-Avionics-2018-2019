#pragma once
#include "pinout.h"

class gs_hardware {

public:

	// ENUMS
	enum class hardware {
		NONE = 0,
		LIN_ACT = 1,
		VALVE = 2
	};
	enum class lin_act_state {
		EXTENDED = 1,
		RETRACTED = 2
	};
	enum class valve_state {
		CLOSED = 0,
		OPEN = 1
	};

	// CONSTRUCTORS
	gs_hardware(int);
	gs_hardware(int, hardware);

	// METHODS
	int getHardwarePin(void);
	hardware getHardwareType(void);
	lin_act_state getLinActState(void);
	valve_state getValveState(void);
	void setHardwareType(hardware);
	void setLinActState(lin_act_state new_state);
	void setValveState(valve_state new_state);

private:

	// VARIABLES

	int gpio_pin;

	hardware hardware_type;
	lin_act_state currentLinActState;
	valve_state currentValveState;



};

