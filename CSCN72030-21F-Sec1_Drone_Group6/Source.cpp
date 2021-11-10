
#include <iostream>
#include "batteryWater.h"

int main() {
	
		std::cout << "Hello, World!" << std::endl;
		connection* connect = new connection((char*)"A1", (char*)"a2");
		batteryWater* temp = new batteryWater();
		cout << "wtr:" << temp->getWaterStorage()<<"\n";
		cout << "ch:" << temp->isCharging() << "\n";
		cout << "Bat:" <<temp->getCurrentBattery() << "\n";
		temp->update();
	return 0;
}