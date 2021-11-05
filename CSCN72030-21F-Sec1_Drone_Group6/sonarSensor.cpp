
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