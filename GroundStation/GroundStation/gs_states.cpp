#include "gs_states.h"


// create hardware
gs_hardware* gs_states::lin_act_LOX = new gs_hardware(PIN_LINACT_LOX, gs_hardware::hardware::LIN_ACT);
gs_hardware* gs_states::lin_act_CH4 = new gs_hardware(PIN_LINACT_CH4, gs_hardware::hardware::LIN_ACT);
gs_hardware* gs_states::valve_LOX = new gs_hardware(PIN_VALVE_LOX, gs_hardware::hardware::VALVE);
gs_hardware* gs_states::valve_CH4 = new gs_hardware(PIN_VALVE_CH4, gs_hardware::hardware::VALVE);

gs_states::gs_states() {
}


int gs_states::transCount(void) {
	return (sizeof(trans) / sizeof(*trans));
}

// GROUND STATION STATE FUNCTIONS

