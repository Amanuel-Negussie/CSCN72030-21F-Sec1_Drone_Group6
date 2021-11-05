#include "connection.h";

class tempSensor {

private:
	char* ID;
	connection* circuit;
public:
	tempSensor(char* ID, connection* circuit);
	~tempSensor();
	float getTemp();
	bool  isOnline();
	char* getID();
};
