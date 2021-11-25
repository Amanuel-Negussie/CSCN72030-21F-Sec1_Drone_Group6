/*
* File : connection.cpp
* Programmer : Danny Smith
* Date : November 5, 2021
* Course : CSCN72030
* Professor : Dr.Elliot coleshill
* group : Islam Ahmed, Nicholas Prince, Amanual Negussie
* Project : Drone
* Version : 1.0
*
* UPDATE HISTORY -
* 1.0 - Base functionality added including ( class connection, logError, getVoltage, testConnection. { Date : November 6, 2021 } - version created by Danny Smith
*/
#include "connection.h";
#include <string>


// see .h file for definitions
bool connection::testConnection(int volts) {
	
	if (getVoltage() == 1) {
		
		return true;
	}
	else {
		logError("Broken Connection");
		return false;
	}
	
} 

// see .h file for definitions


connection::connection(string p1, string p2) {
	this->point1 = p1;
	this->point2 = p2;
}


// see .h file for definitions
int connection::getVoltage() { // designed to read from file. Remove first line so that 0 (Broken connection gets closer to being called
	int voltage;
	char input;
	fstream file;
	fstream temp;
	file.open(CIRCUIT_FILE, ios::in);
	temp.open(TEMP_FILE, ios::out);
	if (!file.is_open()) { // if curcuit file is opened
		logError(" SYSTEM ERROR File Not Opened");
		throw fileNotOpened();
	}
	else {
		file >> input;
		voltage = (int)input;
		if (!temp.is_open()) { // if temp file is opened
			logError(" SYSTEM ERROR File Not Opened");
			throw fileNotOpened();
		}
		else {
			file >> input;
			while (input != 59) { // while not ;
				temp << input;
				file >> input;
			}
		
			switch (voltage) { // append first value at end then EOF (;)
			case 49:
				temp << "1;";
				break;
			case 48:
				temp << "0;";
				break;
			default:
				throw wrongVoltage();		//changes by I& A
				temp << "0;";				//changes by I& A, plz fix
				break;
			}
		}
	}
	file.close();
	remove(CIRCUIT_FILE); // delete original file
	temp.close();

	if (rename(TEMP_FILE, CIRCUIT_FILE)!= 0) { // rename temp file to replace circuit file after proper reading and appending
		logError(" SYSTEM ERROR File Not Renamed");
		throw renameFail();
	}
	switch (voltage) {
	case 49:
		return 1;
		break;
	case 48:
		return 0;
		break;
	default:
		logError(" SYSTEM ERROR Wrong Voltage Passed");
		throw wrongVoltage();		//changes by I& A, plz fix
		//return 0;					//changes by I& A, plz fix
		break;
	}
	return voltage;
}
// see .h file for definitions
bool logError(string msg) {
	

	fstream file;
	file.open(ERROR_LOG, ios::app);
	if (!file.is_open()) {
		throw noErrorLog();
	}
	else {
		// current date/time based on current system
		time_t now = time(0);
		tm* ltm = localtime(&now);
		file << 1900 + ltm->tm_year <<":" << 1 + ltm->tm_mon <<":" << ltm->tm_mday << "  "<< ltm->tm_hour <<":"<< ltm->tm_min <<":"<< ltm->tm_sec << " - ERROR : " << msg <<"\n";
	}
	file.close();
}





