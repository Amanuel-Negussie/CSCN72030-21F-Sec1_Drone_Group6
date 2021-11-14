#pragma once
/*
* File : tempSensor.h
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
	string getID();
};
