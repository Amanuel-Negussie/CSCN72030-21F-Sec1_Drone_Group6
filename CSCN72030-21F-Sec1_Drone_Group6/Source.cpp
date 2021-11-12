
#include <iostream>
#include "batteryWater.h"
#include "FlightController.h"
#include "NavSensor.h"

int main() {
	std::cout << "Hello, World!" << std::endl;
	connection* connect = new connection((char*) "A1", (char*) "a2");


	Coord startingLocation(0, 0);
	FlightController myFC = FlightController(startingLocation, WEST);
	batteryWater bW;

	return 0;
}