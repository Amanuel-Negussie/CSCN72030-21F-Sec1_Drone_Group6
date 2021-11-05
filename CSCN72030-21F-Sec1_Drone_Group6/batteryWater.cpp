#include "batteryWater.h"
#include <iostream>


batteryWater::~batteryWater() {
	for (int counter = 0; counter < MAX_CONNECTIONS; counter++) {
		delete(this->circuit[counter]);
	}
	
}
batteryWater::batteryWater() {
	for (int counter = 0; counter < MAX_CONNECTIONS; counter++) {
		connection* circuit = new connection((char*)"00", (char*)"00");
		this->circuit[counter] = circuit;
	}
	
	this->charging = false;
}