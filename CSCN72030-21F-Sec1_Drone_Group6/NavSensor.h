#pragma once
#include "Coord.h"

#include <vector>
#include <fstream>
#include <string>
using namespace std;

class NavSensor {
protected:
	int gridSize;
	vector<Coord> path;

public:
	NavSensor(int);
	vector<Coord> getNavSensorPath();
	vector<Coord> updatePathCollisionFoundAt(int);
	vector<Coord> updatePathGoHome();
	vector<Coord> updatePathGoChargingStation();
	vector<Coord> updatePathGoWaterStation();
	int getNavSensorSpeed(int);

private:
	void initPath();
	void generateNewPath();
};