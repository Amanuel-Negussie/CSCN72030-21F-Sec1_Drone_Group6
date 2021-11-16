#pragma once
/*
* File : batteryWater.h
* Programmer : Danny Smith
* Date : November 5, 2021
* Course : CSCN72030
* Professor : Dr.Elliot coleshill
* group : Islam Ahmed, Nicholas Prince, Amanual Negussie
* Project : Drone
* Version : 1.1
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

	Version 1.1 - More variables added, Save function Added, setCharging function removed {Date : November 10, 2021 } Version edited by - Danny Smith
*/
#include <iostream>
#include "sonarSensor.h";
#define MAX_CONNECTIONS 50
#define MAX_SENSORS 10
#define ERROR_FILE ""
#define STARTUP_INFO ""
#include <string>
class batteryWater {
public :
	bool decreaseBattery(float watts);
	bool startCharging();
	bool endCharging();
	bool drainWater();
	bool fill(int percent);
	int getFlightEstimate(int speed, int maxW);
	int getCurrentBattery();
	float getWaterStorage();
	bool swapBattery();

	void update();
	bool isCharging();

	bool addTempSensor(string ID, string connection1, string connection2);
	batteryWater();
	~batteryWater();
	void save();

	// move to private after tests
	float MAX_TEMP;
	float waterAlert;
	float batteryAlert;
	// move to private after tests
private:
	float update_Temp;
	bool init;

	bool charging;
	
	void updateScreen();
	float batteryCapacity;
	float waterCapacity;
	bool padConnected;
	tempSensor* temps[MAX_SENSORS];
	sonarSensor* sonar;
	bool door;

	float getTemp();
	bool isConnectedBase();
	bool connectBase();
	bool disconnectBase();
	void sendAlert(string input);
	bool openHatch();
	bool closeHatch();
	int tempCount = 0;
	string currentAlert;
};



struct deleteFail : public exception {
	const char* issue() const throw() {
		return "issue With Deletion";
	}
};