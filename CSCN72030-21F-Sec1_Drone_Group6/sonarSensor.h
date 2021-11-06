/*
* File : sonarSensor.h
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