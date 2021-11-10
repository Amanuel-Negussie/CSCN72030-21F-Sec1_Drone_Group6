/*
* File : batteryWater.h
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
#include <iostream>
#include "sonarSensor.h";
#define MAX_CONNECTIONS 50
#define MAX_SENSORS 10
#define ERROR_FILE ""
#define STARTUP_INFO ""

class batteryWater {
public :
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
	batteryWater();
	~batteryWater();
private:
	
	bool charging;
	connection* circuit[MAX_CONNECTIONS];

	
	float batteryCapacity;
	float waterCapacity;
	bool padConnected;
	tempSensor* temps[MAX_SENSORS];
	sonarSensor* sonar;
	bool door;
	void verifyConnections();
	int getTemp();
	bool isConnectedBase();
	bool connectBase();
	bool disconnectBase();
	void sendAlert();
	bool openHatch();
	bool closeHatch();
};



struct deleteFail : public exception {
	const char* issue() const throw() {
		return "issue With Deletion";
	}
};