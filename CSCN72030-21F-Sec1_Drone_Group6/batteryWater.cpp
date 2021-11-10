/*
* File : batteryWater.cpp
* Programmer : Danny Smith
* Date : November 5, 2021
* Course : CSCN72030
* Professor : Dr.Elliot coleshill
* group : Islam Ahmed, Nicholas Prince, Amanual Negussie
* Project : Drone
* Version : 1.0
*
* UPDATE HISTORY -
* 1.0 - Base Functionality created : 	
	bool decreaseBattery(int watts);
	bool startCharging();
	bool endCharging();
	bool drainWater();
	bool fill(int percent);
	int getFlightEstimate(int speed, int maxW);
	int getCurrentBattery();
	int getWaterStorage();
	bool swapBattery();
	bool connections[MAX_CONNECTIONS+(MAX_SENSORS+1)];
	void update();
	bool isCharging();
	bool addTempSensor(char* ID, char* connection1, char* connection2);
	void verifyConnections();
	int getTemp();
	bool isConnectedBase();
	bool setCharging(bool charging);
	bool connectBase();
	bool disconnectBase();
	void sendAlert();
	bool openHatch();
	bool closeHatch();
	batteryWater();
	~batteryWater();

	Variables - 
	bool charging;
	connection* circuit[MAX_CONNECTIONS];
	int batteryCapacity;
	int waterCapacity;
	bool padConnected;
	tempSensor* temps[MAX_SENSORS];
	sonarSensor* sonar;
	bool door;

	Exceptions - 
	deleteFail
	------------------------ { Date : November 6, 2021 } Version Created by - Danny Smith
*/
#include "batteryWater.h"
#include <iostream>


batteryWater::~batteryWater() {
	for (int counter = 0; counter < MAX_CONNECTIONS; counter++) {
		delete(this->circuit[counter]);
		
	}
	for (int counter = 0; counter < MAX_SENSORS; counter++) {
		if (this->temps[counter] != NULL) {
			delete(this->temps[counter]);
		}
	}
	try { // unsure if this will already be done in the above loop
		delete[] temps;
	}
	catch (deleteFail()) {

	}
	delete(this->sonar);
	
}
batteryWater::batteryWater() {
	for (int counter = 0; counter < MAX_CONNECTIONS; counter++) {
		connection* circuit = new connection((char*)"00", (char*)"00");
		this->circuit[counter] = circuit;
		this->connections[counter] = 1;
	}
	for (int counter = MAX_CONNECTIONS; counter < MAX_CONNECTIONS + MAX_SENSORS + 1; counter++) { // this depends on the < MAX_CONNECTIONS in the loop above if the < conditions changes this one should to
		this->connections[counter] = 1;
	}

	// set default values
	this->charging = false;
	this->batteryCapacity = 0;
	this->door = false;
	this->padConnected = false;
	this->waterCapacity = 0;

	// create default sonar
	connection* con = new connection((char*)"A1", (char*)"A2");
	sonarSensor* sensor = new sonarSensor((char*)"001", con);
	this->sonar = sensor;

	//create default temp
	connection* con2 = new connection((char*)"A3", (char*)"A4");
	tempSensor* temp = new tempSensor((char*)"002", con2);
	this->temps[0] = temp;

	// initialize array of temps
	for (int counter = 1; counter < MAX_SENSORS; counter++) {
		this->temps[counter] = NULL;
	}

	
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
