#include "b1_hardware.h"



b1_hardware::b1_hardware() {

	hardwareType = hardware::NONE;

}


// GETTERS
b1_hardware::hardware b1_hardware::getHardwareType(void) {
	return hardwareType;
}
b1_hardware::sol_state b1_hardware::getSolState(void) {
	return currentSolState;
}
b1_hardware::vent_state b1_hardware::getVentState(void) {
	return currentVentState;
}
b1_hardware::pyro_state b1_hardware::getPyroState(void) {
	return currentPyroState;
}

// SETTERS
void b1_hardware::setHardwareType(b1_hardware::hardware newHardware) {
	hardwareType = newHardware;
}
void b1_hardware::setSolState(b1_hardware::sol_state newState) {
	currentSolState = newState;
}
void b1_hardware::setVentState(b1_hardware::vent_state newState) {
	currentVentState = newState;
}
void b1_hardware::setPyroState(b1_hardware::pyro_state newState) {
	currentPyroState = newState;
}




