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



tempSensor::tempSensor(string ID, connection* circuit) {
	this->ID = ID;
	this->circuit = circuit;
}
tempSensor::~tempSensor() {
	delete(this->circuit);
}
float tempSensor::getTemp() {
	int x = 0;
	char input;
	int count = 0;
	char word[WORD_SIZE];
	fstream file;
	fstream temp;
	file.open(TEMPS_FILE, ios::in);
	temp.open(TEMP_FILE, ios::out);
	float temperature = 0;
	if (!file.is_open()) { // if curcuit file is opened
		logError(" SYSTEM ERROR File Not Opened");
		throw fileNotOpened();
	}
	else {

		if (!temp.is_open()) { // if temp file is opened
			logError(" SYSTEM ERROR File Not Opened");
			throw fileNotOpened();
		}
		else {
			file >> input;
			while (input != 59 && input != 38) {
				word[x] = input;
				file >> input;
				x++;
			} // while not ; or &
			word[x] = '\0';
			temperature = atof(word);
			file >> input;
			while (input != 38){
				temp << input;
				if (input == 59) {
					temp << "\n";
				}
				file >> input;
			}
			temp << ";\n" <<temperature << "&";
		}

	}
	file.close();
	remove(TEMPS_FILE); // delete original file
	temp.close();

	if (rename(TEMP_FILE, TEMPS_FILE) != 0) { // rename temp file to replace circuit file after proper reading and appending
		logError(" SYSTEM ERROR File Not Renamed");
	
	}
	return temperature;
}
bool tempSensor::isOnline() {
	return this->circuit->testConnection(1);
}
string tempSensor::getID() {
	return this->ID;
}