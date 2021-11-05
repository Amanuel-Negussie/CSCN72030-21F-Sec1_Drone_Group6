

#include "sonarSensor.h";
#define MAX_CONNECTIONS 50

class batteryWater {
public :
	connection* circuit[MAX_CONNECTIONS];
	batteryWater();
	~batteryWater();
private:
	bool charging;
	
};
