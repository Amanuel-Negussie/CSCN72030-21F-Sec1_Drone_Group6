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