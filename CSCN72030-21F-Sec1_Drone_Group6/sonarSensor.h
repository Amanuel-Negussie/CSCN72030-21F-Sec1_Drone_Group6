

#include "tempSensor.h";

class sonarSensor {

private:
	char* ID;
	connection* circuit;
public:
	bool isOnline();
	char* getID();
	double getTime();
	sonarSensor(char* ID, connection* circuit);
	~sonarSensor();
};