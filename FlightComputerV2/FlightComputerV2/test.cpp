//
//  _      ___   _          _    __   __  ___    ___    _  _   ___    ___   ___ 
// | |    | _ \ | |        /_\   \ \ / / |_ _|  / _ \  | \| | |_ _|  / __| / __|
// | |__  |   / | |__     / _ \   \ V /   | |  | (_) | | .` |  | |  | (__  \__ \
// |____| |_|_\ |____|   /_/ \_\   \_/   |___|  \___/  |_|\_| |___|  \___| |___/
//
// Organization:  Liquid Bi-Propellant Rocket Project
// University:    California State Polytechnic University, Pomona
// Author:        Cole Edwards
// Date Created:  23 October 2018
// Date Revised:  23 October 2018
// File Name:     test.cpp
// Description:   Sample Template.  This file is not to be included in the final
//                build.  It is a formatting template for all other files.
//
//
// GENERAL TODOS
//
// INCLUDES
//#include <wiringPi.h>

//LED Pin - wiringPi pin 0 is BCM_GPIO 17.
//we have to use BCM numbering when initializing with wiringPiSetupSys
//when choosing a different pin number please use the BCM numbering, also
//update the Property Pages - Build Events - Remote Post-Build Event command
//which uses gpio export for setup for wiringPiSetupSys
//#define	LED	17

//int test(void)
//{
//	wiringPiSetupSys();
//
//	pinMode(LED, OUTPUT);
//
//	while (true)
//	{
//		digitalWrite(LED, HIGH);  // On
//		delay(500); // ms
//		digitalWrite(LED, LOW);	  // Off
//		delay(500);
//	}
//	return 0;
//}