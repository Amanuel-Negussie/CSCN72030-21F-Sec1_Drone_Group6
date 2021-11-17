#pragma once
/*
* File : tempSensor.h
* Programmer : Danny Smith
* Date : November 5, 2021
* Course : CSCN72030
* Professor : Dr.Elliot coleshill
* group : Islam Ahmed, Nicholas Prince, Amanual Negussie
* Project : Drone
* Version : 1.1
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

1.1 - ID changed to string { November 15, 2021 } by - Danny Smith
*/
#include "connection.h";

class tempSensor {

private:
	
	string ID;
	connection* circuit;
public:
	

	tempSensor(string ID, connection* circuit);
	~tempSensor();
	float getTemp();
	bool  isOnline();
	string getID();
};
