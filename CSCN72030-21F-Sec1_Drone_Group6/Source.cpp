
#include <iostream>
#include "batteryWater.h" // NOTE EVERY UPDATE CALL WAITS ONE SECOND ( This is done to prevent file errors )

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