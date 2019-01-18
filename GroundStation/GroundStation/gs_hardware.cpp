#include "gs_hardware.h"


gs_hardware::gs_hardware(int pin) {

	gpio_pin = pin;
	hardware_type = hardware::NONE;
	currentLinActState = lin_act_state::EXTENDED;
	currentValveState = valve_state::CLOSED;

}
gs_hardware::gs_hardware(int pin, gs_hardware::hardware type) {

	gpio_pin = pin;
	hardware_type = type;

	switch (hardware_type)
	{
	case gs_hardware::hardware::NONE:
		break;
	case gs_hardware::hardware::LIN_ACT:
		break;
	case gs_hardware::hardware::VALVE:
		break;
	default:
		break;
	}

}

// GETTERS
int gs_hardware::getHardwarePin(void) {
	return gpio_pin;
}
gs_hardware::hardware gs_hardware::getHardwareType(void) {
	return hardware_type;
}
gs_hardware::lin_act_state gs_hardware::getLinActState(void) {
	return currentLinActState;
}
gs_hardware::valve_state gs_hardware::getValveState(void) {
	return currentValveState;
}

// SETTERS
void gs_hardware::setHardwareType(gs_hardware::hardware type) {
	if (hardware_type == hardware::NONE) {
		hardware_type = type;
	}
}


// STATE SETTERS

void gs_hardware::setLinActState(gs_hardware::lin_act_state new_state) {
	
	// TODO: digitalwrite, set the state of the pin
	switch (new_state)
	{
	case gs_hardware::lin_act_state::EXTENDED:
		break;
	case gs_hardware::lin_act_state::RETRACTED:
		break;
	default:
		break;
	}

	currentLinActState = new_state;

}
void gs_hardware::setValveState(gs_hardware::valve_state new_state) {
	
	// TODO: digitalwrite, set the state of the pin
	switch (new_state)
	{
	case gs_hardware::valve_state::CLOSED:
		break;
	case gs_hardware::valve_state::OPEN:
		break;
	default:
		break;
	}

	currentValveState = new_state;

}
