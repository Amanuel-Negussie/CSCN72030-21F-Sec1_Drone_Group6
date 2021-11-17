#pragma once
#include "Coord.h"
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
	int userPathSelection();
	vector<Coord> getNavSensorPath();
	vector<Coord> updatePathCollisionFoundAt(int);
	vector<Coord> updatePathGoHome(int);
	bool checkIfHome(int);
	int getNavSensorSpeed(int);

private:
	void initPath();
	void generateNewPath();
};