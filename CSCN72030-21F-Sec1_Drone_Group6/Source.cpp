
#include <iostream>
#include "batteryWater.h"

int main() {
	
		std::cout << "Hello, World!" << std::endl;
		connection* connect = new connection((char*)"A1", (char*)"a2");
		batteryWater* temp = new batteryWater();
		temp->update();
		
		for (int i = 0; i < 25; i++) {
			temp->decreaseBattery(20);
		}
		//cout << temp->MAX_TEMP;
	return 0;
}