
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
	void logError(FILE);
	bool charging;
	connection* circuit[MAX_CONNECTIONS];
	const char* errorCodes;
	const char* startupInfo;
	
	int batteryCapacity;
	int waterCapacity;
	bool padConnected;
	tempSensor* temps[MAX_SENSORS];
	sonarSensor* sonars[MAX_SENSORS];
	bool door;
	void verifyConnections();
	int getTemp();
	bool isConnectedBase();
	bool setCharging(bool charging);
	bool connectBase();
	bool disconnectBase();
	void sendAlert();
	bool openHatch();
	bool closeHatch();
};
