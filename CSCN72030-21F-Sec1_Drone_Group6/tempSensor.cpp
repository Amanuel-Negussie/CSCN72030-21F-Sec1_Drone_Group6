/*
* File : tempSensor.cpp
* Programmer : Danny Smith
* Date : November 5, 2021
* Course : CSCN72030
* Professor : Dr.Elliot coleshill
* group : Islam Ahmed, Nicholas Prince, Amanual Negussie
* Project : Drone
* Version : 1.0
*
* UPDATE HISTORY -
* 1.0 - Base functionality added :
	tempSensor(char* ID, connection* circuit);
	~tempSensor();
	float getTemp();
	bool  isOnline();
	char* getID();

	Variables -
	char* ID;
	connection* circuit;

--------------- { Date : November 6, 2021 } - version created by Danny Smith
*/
# include "tempSensor.h"


tempSensor::tempSensor(char* ID, connection* circuit) {
	this->ID = ID;
	this->circuit = circuit;
}
tempSensor::~tempSensor() {
	delete(this->circuit);
}
float tempSensor::getTemp() {
	return 64.87;
}
bool tempSensor::isOnline() {
	return this->circuit->testConnection(1);
}
char* tempSensor::getID() {
	return this->ID;
}