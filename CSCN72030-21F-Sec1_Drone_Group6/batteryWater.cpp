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
bool batteryWater::decreaseBattery(int watts) {
	return true;
}
bool batteryWater::startCharging() {
	return true;
}
bool batteryWater::endCharging() {
	return true;
}
bool batteryWater::drainWater() {
	return true;
}
bool batteryWater::fill(int percent) {
	return true;
}
int batteryWater::getFlightEstimate(int speed, int maxW) {
	return 1;
}
int batteryWater::getCurrentBattery() {
	return 1;
}
int batteryWater::getWaterStorage() {
	return 1;
}
bool batteryWater::swapBattery() {
	return true;
}
void batteryWater::update() {

}
bool batteryWater::isCharging() {
	return true;
}
bool batteryWater::addTempSensor(char* ID, char* connection1, char* connection2) {
	return true;
}


void batteryWater::verifyConnections() {

}
int batteryWater::getTemp() {
	return 1;
}
bool batteryWater::isConnectedBase() {
	return true;
}
bool batteryWater::setCharging(bool charging) {
	return true;
}
bool batteryWater::connectBase() {
	return true;
}
bool batteryWater::disconnectBase() {
	return true;
}
void batteryWater::sendAlert() {

}
bool batteryWater::openHatch() {
	return true;
}
bool batteryWater::closeHatch() {
	return true;
}
void batteryWater::logError(FILE) {

}