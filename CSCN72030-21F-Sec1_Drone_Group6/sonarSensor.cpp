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
	//********** Distance Calculation Air*************
	// Speed of sound in air = 343 M/s
	// 343m = 1125f
	// 1125 feet / 2 feet tank = 562 laps/second
	// therefor full tank = 1s/562 = 0.00177935943s
	// therefor an empty tank is 1.7793ms


	//********** Distance Calculation Water*************
	// Speed of sound in air = 1482 M/s
	// 343m = 4862f
	// 4862 feet / 2 feet tank = 2431 laps/second
	// therefor full tank = 1s/2431 = 0.000411353353
	// therefor an empty tank is 0.4113ms

	// to conlude the return value should be between 0.4113 and 1.7793
	int x = 0;
	char input;
	char word[5];
	fstream file;
	file.open(STARTUP_FILE, ios::in);
	if (!file.is_open()) { // if curcuit file is opened
		throw fileNotOpened();
	}
	else {
		file >> input;
		while (input != 59 && input !=38) {
			
			word[x] = input;
			file >> input;
			
			x++;
		}
		word[x] = '\0';
	}
	file.close();
	return atof(word);;
}


sonarSensor::sonarSensor(char* ID, connection* circuit) {
	this->circuit = circuit;
	this->ID = ID;
}
sonarSensor::~sonarSensor() {
	delete (this->circuit);
}