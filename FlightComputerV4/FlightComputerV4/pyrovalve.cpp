#include "pyrovalve.h"


// CONSTRUCTOR
pyrovalve::pyrovalve(int pin, pyrovalve::pyroType type) {

	this->setHardwarePin(pin);
	this->type = type;
	initialize();

}


// METHODS

// ... initialize the pyrovalve ... //
void pyrovalve::initialize(void) {

	digitalWrite(this->getHardwarePin(), HIGH);

	switch (type)
	{
	case pyrovalve::NO:
		state = pyroState::OPEN;
		break;
	case pyrovalve::NC:
		state = pyroState::CLOSED;
		break;
	default:
		break;
	}

}

// ... detonate the pyrovalve ... //
void pyrovalve::detonate(void) {

	digitalWrite(this->getHardwarePin(), LOW);
	std::thread(cutPower, this->pyroCutOffDelayMS, this->getHardwarePin()).detach();

	switch (type)
	{
	case pyrovalve::NO:
		state = pyroState::CLOSED;
		break;
	case pyrovalve::NC:
		state = pyroState::OPEN;
		break;
	default:
		break;
	}

}

// ... Cut power to the pyrovalve to prevent overcurrenting ... //
void pyrovalve::cutPower(int delay, int pin) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	digitalWrite(pin, HIGH);
}

// GETTERS
pyrovalve::pyroType pyrovalve::getPyroType(void) {
	return this->type;
}
pyrovalve::pyroState pyrovalve::getCurrentState(void) {
	return this->state;
}
