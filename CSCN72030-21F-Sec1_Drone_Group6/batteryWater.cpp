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
#define WORD_SIZE 5

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
	this->charging = false;
	this->batteryCapacity = 0;
	this->door = false;
	this->padConnected = false;
	this->waterCapacity = 0;
	for (int counter = 0; counter < MAX_CONNECTIONS; counter++) {
		connection* circuit = new connection((char*)"00", (char*)"00");
		this->circuit[counter] = circuit;
		this->connections[counter] = 1;
	}
	for (int counter = MAX_CONNECTIONS; counter < MAX_CONNECTIONS + MAX_SENSORS + 1; counter++) { // this depends on the < MAX_CONNECTIONS in the loop above if the < conditions changes this one should to
		this->connections[counter] = 1;
	}

	// set default values

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

	// init water capacity send issue if sonar is offline
	if (sonar->isOnline()) {
		this->waterCapacity = ((sensor->getTime()-0.4113) / 1.7793) *100;
	}
	else {
		this->sendAlert("SONAR OFFLINE");
	}
	int x = 0;
	char input;
	int count = 0;
	char word[WORD_SIZE];
	fstream file;
	file.open(STARTUP_FILE, ios::in);
	if (!file.is_open()) { // if curcuit file is opened
		throw fileNotOpened();
	}
	else {
		file >> input;
		while (input != 38) {
			while (input != 59 && input != 38) {
				
				word[x] = input;
				file >> input;
				
				x++;
			} // while not ;
			word[x] = '\0';

			if (count == 0) {
				for (int i = 0; i < WORD_SIZE; i++) { // reset word
					word[i] = '\0';
					x = 0;
				} // ignore first element
			}
			if (count == 1) {
				if (atoi(word) == 1) {
					this->startCharging();
				}
				else {
					this->endCharging();
				}
				for (int i = 0; i < WORD_SIZE; i++) { // reset word
					word[i] = '\0';
					x = 0;
				} // if charging or not
			} // check charging

			if (count == 2) {
				if (atoi(word) == 1) {
					this->openHatch();
				}
				else {
					this->closeHatch();
				}
				for (int i = 0; i < WORD_SIZE; i++) { // reset word
					word[i] = '\0';
					x = 0;
				} // if charging or not
			} // check charging


			if (count == 3) {
				if (atoi(word) == 1) {
					this->connectBase();
				}
				else {
					this->disconnectBase();
				}
				for (int i = 0; i < WORD_SIZE; i++) { // reset word
					word[i] = '\0';
					x = 0;
				} // if charging or not
			} // check charging

			if (count == 4) {
				this->batteryCapacity = atoi(word);
			} // check charging
				count++;
				file >> input;
		} // while ! &
		
	}
	file.close();

}








bool batteryWater::decreaseBattery(int watts) {
	//watts = 50
	// 20w/h = 20w/h / 240 apx 15 sec
	float temp = this->batteryCapacity;
	this->batteryCapacity = this->batteryCapacity - (watts / 240);
	if (this->batteryCapacity != temp) {
		return true;
	}
	else {
		return false;
	}
	
}
bool batteryWater::startCharging() {
	this->charging = true;
	if (this->charging == true) {
		return true;
	}
	else {
		return false;
	}
}
bool batteryWater::endCharging() {
	this->charging = false;
	if (this->charging == false) {
		return true;
	}
	else {
		return false;
	}
}
bool batteryWater::drainWater() {
	this->waterCapacity = 0;
	if (this->getWaterStorage() == 0) {
		return true;
	}
	else {
		return true;
	}
}
bool batteryWater::fill(int percent) {
	this->waterCapacity = percent;
	if (this->getWaterStorage() == percent) {
		return true;
	}
	else {
		return false;
	}
}
int batteryWater::getCurrentBattery() {
	return this->batteryCapacity;
}
int batteryWater::getWaterStorage() {
	return this->waterCapacity;
}
bool batteryWater::isCharging() {
	return this->charging;
}
bool batteryWater::isConnectedBase() {
	return this->padConnected;
}
bool batteryWater::connectBase() {
	this->padConnected = true;
	if (this->isConnectedBase()== true) {
		return true;
	}
	else {
		return false;
	}
}
bool batteryWater::disconnectBase() {
	this->padConnected = false;
	if (this->isConnectedBase() == false) {
		return true;
	}
	else {
		return false;
	}
}
bool batteryWater::openHatch() {
	this->door = true;
	if (this->door == true) {
		return true;
	}
	else {
		return false;
	}
}
bool batteryWater::closeHatch() {
	this->door = false;
	if (this->door == false) {
		return true;
	}
	else {
		return false;
	}
}








void batteryWater::sendAlert(string input) {

}

bool batteryWater::addTempSensor(char* ID, char* connection1, char* connection2) {
	return true;
}
void batteryWater::verifyConnections() {

}
int batteryWater::getTemp() {
	return 1;
}
void batteryWater::update() {

}
bool batteryWater::swapBattery() {
	return true;
}
int batteryWater::getFlightEstimate(int speed, int maxW) {
	return 1;
}