#pragma once
#include "Coord.h"
#include "Alert.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class NavSensor {
protected:
	int gridSize;
	Coord home;
	vector<Coord> path;

public:
	NavSensor();
	NavSensor(int);
	vector<Coord> getNavSensorPath(); //retrieve path from file
	vector<Coord> updatePathCollisionFoundAt(int); //collision handling (update path to go around collision)
	vector<Coord> updatePathGoHome(int); //make drone go home and back to last position in path (instance where drone was told to go home)
	bool checkIfHome(int); //check if current Coord matches 'home' Coord
	int getNavSensorSpeed(int); //generate nav speed based on actual speed from flightController
	Coord getCurrentCoord(int); //getter for current Coord in path

private:
	void initPath(); //retrieve path from file
};