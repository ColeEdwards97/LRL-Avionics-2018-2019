// 
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//                
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  12 October 2018
// Date Revised:  12 October 2018
// Description:   Bronco 1 Hardware definition
//
//
// GENERAL TODOS
//
// INCLUDES
#pragma once


// TODO: consider abstracting

class b1_hardware {

public:

	// ENUMS
	enum class hardware {
		NONE = -1,
		SOLENOID = 0,
		VENT = 1,
		PYRO = 2
	};
	enum class sol_state {
		ERROR = -1,
		CLOSED = 0,
		OPEN = 1,
	};
	enum class vent_state {
		ERROR = -1,
		CLOSED = 0,
		OPEN = 1,
	};
	enum class pyro_state {
		ERROR = -1,
		INTACT = 0,
		BURST = 1
	};

	// CONSTRUCTOR
	b1_hardware();

	// METHODS
	hardware getHardwareType(void);
	sol_state getSolState(void);
	vent_state getVentState(void);
	pyro_state getPyroState(void);
	void setHardwareType(hardware newType);
	void setSolState(sol_state newState);
	void setVentState(vent_state newState);
	void setPyroState(pyro_state newState);

private:

	hardware hardwareType;

	sol_state currentSolState;
	vent_state currentVentState;
	pyro_state currentPyroState;

};

