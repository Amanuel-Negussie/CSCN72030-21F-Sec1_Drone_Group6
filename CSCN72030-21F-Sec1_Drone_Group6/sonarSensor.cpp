/*
* File : sonarSensor.cpp
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
	bool isOnline();
	char* getID();
	double getTime();
	sonarSensor(char* ID, connection* circuit);
	~sonarSensor();

	Variables -
	char* ID;
	connection* circuit;

--------------- { Date : November 6, 2021 } - version created by Danny Smith
*/
#include "sonarSensor.h";


bool sonarSensor::isOnline() {
	return circuit->testConnection(1);
}


char* sonarSensor::getID() {
	return (char*)this->ID;
}


double sonarSensor::getTime() {
	return 2.0;
}


sonarSensor::sonarSensor(char* ID, connection* circuit) {
	this->circuit = circuit;
	this->ID = ID;
}
sonarSensor::~sonarSensor() {
	delete (this->circuit);
}