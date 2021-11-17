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
	int selection;
	int gridSize;
	Coord home;
	vector<Coord> path;

public:
	NavSensor();
	int userPathSelection(); //user selects path file
	vector<Coord> getNavSensorPath(); //retrieve path from file
	vector<Coord> updatePathCollisionFoundAt(int); //collision handling (update path to go around collision)
	vector<Coord> updatePathGoHome(int); //make drone go home and back to last position in path (instance where drone was told to go home)
	bool checkIfHome(int); //check if current Coord matches 'home' Coord
	int getNavSensorSpeed(int); //generate nav speed based on actual speed from flightController
	Coord getCurrentCoord(int); //getter for current Coord in path

private:
	void initPath(); //retrieve path from file
	//void generateNewPath(); //generate a full path (not used in final)
};