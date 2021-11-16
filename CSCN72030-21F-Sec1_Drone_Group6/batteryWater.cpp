/*
* File : batteryWater.cpp
* Programmer : Danny Smith
* Date : November 5, 2021
* Course : CSCN72030
* Professor : Dr.Elliot coleshill
* group : Islam Ahmed, Nicholas Prince, Amanual Negussie
* Project : Drone
* Version : 1.2
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

	Version 1.1 - Save Added { Date : November 10, 2021 } Version updated by - Danny Smith
	Version 1.2 - wait Added to save function NOTE : only works on windows systems{ Date : November 10, 2021 } Version updated by - Danny Smith


	BUG LOG
	1 - Once in apx 40 runs water capacity will drop to zero percent - Suspision due to currupt files or excessive opening and closing
	2 - Temperature sensors can only read 1 I cannot read more then one sensor in this->getTemp()


	FIX LOG 
	1 - Fixed by adding a 1 second wait after saving to prevent rapid read writes and causing a corruption
*/
#include "batteryWater.h"
#include <iostream>
#ifdef _WIN64 // only use on windows machine
#include <Windows.h>
#endif 

batteryWater::~batteryWater() {



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

	this->init = true;
	this->update_Temp=0;
	// read below info from rule file
	this->MAX_TEMP = 70;
	this->waterAlert = 20;
	this->batteryAlert = 40;

	this->charging = false;
	this->batteryCapacity = 0;
	this->door = false;
	this->padConnected = false;
	this->waterCapacity = 0;

	// set default values

	// create default sonar
	connection* con = new connection((char*)"A1", (char*)"A2");
	sonarSensor* sensor = new sonarSensor((char*)"001", con);
	this->sonar = sensor;

	//create default temp						// should read from file
	int x = 0;
	char input;
	int count = 0;
	char word[WORD_SIZE];

	string analog1;
	string analog2;
	string idtmp;
	fstream file3;
	file3.open(SENSORS_FILE, ios::in);
	if (!file3.is_open()) { // if curcuit file is opened
		logError("SYSTEM ERROR File Not Opened");
		throw fileNotOpened();
	}
	else {
		file3 >> input;
		while (input != 38) {
			while (input != 59 && input != 38) {

				word[x] = input;
				file3 >> input;

				x++;
			} // while not ;
			word[x] = '\0';
			if (count == 0) {
				analog1 = word;
			}
			else if (count == 1) {
				analog2 = word;
			}
			else if (count == 2) {
				idtmp = word;
				count = 0;
				this->addTempSensor(idtmp, analog1, analog2);
			}
			for (int i = 0; i < WORD_SIZE; i++) { // reset word
				word[i] = '\0';
				x = 0;
			} // if charging or not
			count++;
			file3 >> input;
			
		}
	}
	file3.close();
	





	//
	connection* con2 = new connection((char*)"A3", (char*)"A4");
	tempSensor* temp = new tempSensor((char*)"002", con2);
	this->temps[0] = temp;
	this->tempCount=1;

	// initialize array of temps
	for (int counter = 1; counter < MAX_SENSORS; counter++) {
		this->temps[counter] = NULL;
	}

	// init water capacity send issue if sonar is offline
	if (sonar->isOnline()) {
		this->waterCapacity = sensor->getTime();

	}
	else {
		logError("Sonar Damaged");
		this->sendAlert("SONAR OFFLINE");
	}
	x = 0;
	for (int i = 0; i < WORD_SIZE; i++) { // reset word
		word[i] = '\0';
		x = 0;
	} // ignore first element
	count = 0;
	fstream file;
	file.open(STARTUP_FILE, ios::in);
	if (!file.is_open()) { // if curcuit file is opened
		logError("SYSTEM ERROR File Not Opened");
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

			if (count == 3) {
				this->batteryCapacity = atoi(word);
			} // check charging
			count++;
			file >> input;
		} // while ! &

	}
	for (int i = 0; i < WORD_SIZE; i++) { // reset word
		word[i] = '\0';
		x = 0;
	} // ignore first element
	file.close();
	fstream file2;
	count = 0;
	file2.open(RULES_FILE, ios::in);
	if (!file2.is_open()) { // if rules file is opened
		logError("SYSTEM ERROR File Not Opened");
		throw fileNotOpened();
	}

	else {
		file2 >> input;
		while (input != 38) {
			while (input != 59 && input != 38) {

				word[x] = input;
				file2 >> input;

				x++;
			} // while not ;
			
			word[x] = '\0';
			if (count == 0) {
				
				this->MAX_TEMP = atof(word);
			}
			else if (count == 1) {
				this->waterAlert = atof(word);
			}
			else if (count == 2) {

				this->batteryAlert = atof(word);;
			}
			count++;
			for (int i = 0; i < WORD_SIZE; i++) { // reset word
				word[i] = '\0';
				x = 0;
			} // ignore first element
			file2 >> input;
		}
	}
	file2.close();
	this->init = false;
} // initializer


void batteryWater::save() {
	fstream file;
	file.open(STARTUP_FILE, ios::out);
	if (!file.is_open()) { // if curcuit file is opened
		logError(" SYSTEM ERROR File Not Opened");
		throw fileNotOpened();
		
	}
	else {
		file << this->getWaterStorage() << ";\n"; // <causes a bug if you use more then one decimal point
		file << this->isCharging() << ";\n";
		file << this->isCharging() << ";\n";
		file << this->getCurrentBattery() << "&\n";
	}
	file.close();
#ifdef _WIN64 // only use on windows machine
	Sleep(1000);
#endif 

}


bool batteryWater::decreaseBattery(float watts) {
	
	float temp = this->batteryCapacity;
	this->batteryCapacity = this->batteryCapacity - (watts/8); 
	if (this->batteryCapacity != temp) {
		this->update();
		return true;
	}
	else {
		this->update();
		return false;
	}
	
}
bool batteryWater::startCharging() {
	this->charging = true;
	if (this->charging == true) {
		this->update();
		return true;
	}
	else {
		this->update();
		return false;
	}
}
bool batteryWater::endCharging() {
	this->charging = false;
	if (this->charging == false) {
		this->update();
		return true;
	}
	else {
		this->update();
		return false;
	}
}
bool batteryWater::drainWater() {
	this->waterCapacity = 0;
	if (this->getWaterStorage() == 0) {
		this->update();
		return true;
	}
	else {
		this->update();
		return true;
	}
}
bool batteryWater::fill(int percent) {
	this->waterCapacity = percent;
	if (this->getWaterStorage() == percent) {
		this->update();
		return true;
	}
	else {
		this->update();
		return false;
	}
}
int batteryWater::getCurrentBattery() {
	return this->batteryCapacity;
}
float batteryWater::getWaterStorage() {
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
		this->update();
		return true;
	}
	else {
		this->update();
		return false;
	}
}
bool batteryWater::disconnectBase() {
	this->padConnected = false;
	if (this->isConnectedBase() == false) {
		this->update();
		return true;
	}
	else {
		this->update();
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
	this->currentAlert = input;
}

bool batteryWater::addTempSensor(string ID, string connection1, string connection2) {
	connection* con2 = new connection(connection1, connection2);
	tempSensor* temp = new tempSensor(ID, con2);
	this->temps[tempCount] = temp;
	
	this->tempCount = this->tempCount + 1;
	return true;
}





float batteryWater::getTemp() { // errors when getting more then 1 needs to be fixed
	
	float temp = 0;
	for (int counter = 0; counter <= this->tempCount; counter++) {
			
			temp = temps[counter]->getTemp();
		}

	return temp ;
}
void batteryWater::update() { // keep most important errors on the bottom 
	if (!init) { // only make changes if the system is not initializing
	// ensure water is within paramaters
		this->currentAlert = "";
		if (this->waterCapacity > 100) {
			this->waterCapacity = 100;
		}
		if (this->waterCapacity < 0) {
			this->waterCapacity = 0;
		}

		// ensure battery is within paramaters

		if (this->batteryCapacity > 100) {
			this->batteryCapacity = 100;
		}
		if (this->batteryCapacity < 0) {
			this->batteryCapacity = 0;
		}

		// Check Water Capacity

		if (this->waterCapacity <= waterAlert / 2) {
			logError("Water Critical");
			this->sendAlert("WaterCritical");
		}
		else if (this->waterCapacity <= waterAlert) {
			logError("Low Water");
			this->sendAlert("LowWater");
		}

		// check sonar Sensor
		if (!this->sonar->isOnline()) {
			logError("Sonar Sensor " + this->sonar->getID() + " Is Offline");
			this->sendAlert("SonarSensorOffline");
		}



		// check Battery Capacity

		if (this->batteryCapacity <= batteryAlert / 2) {
			logError("battery Critical");
			this->sendAlert("BatteryCritical");
		}
		else if (this->batteryCapacity <= batteryAlert) {
			cout << "HI";
			logError("Low Battery");
			this->sendAlert("LowBattery");
		}

		// check temps and temp sensor
		if (this->temps[0]->isOnline()) {
			float temp = 0;
			temp = this->getTemp();

			this->update_Temp = temp;
			if (temp > this->MAX_TEMP) {
				logError("Max Temp Exceeded : " + to_string(this->MAX_TEMP) + "Current Temp : " + to_string(temp));
				this->sendAlert("MaxTempExceeded");
			}
			else if (temp > this->MAX_TEMP - 10) {
				logError("High Temperature : " + to_string(temp));
				this->sendAlert("MaxTempApproaching");
			}
		} // if temp sensor is online ensure good temps
		else { // log it
			logError("Temperature Sensor " + this->temps[0]->getID() + " is offline");
			this->sendAlert("TemperatureSensorOffline");
		}

		if (this->isCharging()) { // if battery is charging increase battery
			this->batteryCapacity++;
		}
		if (this->door) { // if door open reduce water because its spreading
			this->waterCapacity--;
		}


		this->save();
		this->updateScreen();
	}
}
bool batteryWater::swapBattery() {
	this->connectBase();
	this->startCharging();
	this->batteryCapacity = 100;
	this->endCharging();
	this->disconnectBase();
	return true;
}

void batteryWater::updateScreen() {
	cout << "\x1B[2J\x1B[H"; // <- cls
	cout << "Battery : " << this->getCurrentBattery() << "%                 " << "Water : " << this->getWaterStorage() << "%" << "                Alert :" << this->currentAlert << "            Temperature : " << this->update_Temp<< trunc(this->getTemp()); "\n";
}

int batteryWater::getFlightEstimate(int speed, int maxW) {
	return 1;
}

