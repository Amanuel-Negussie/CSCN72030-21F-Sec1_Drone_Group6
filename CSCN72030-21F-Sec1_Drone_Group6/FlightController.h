#pragma once

#include <vector>
#include <math.h>
#include <Eigen/Dense>
#include <numeric>

#include "Location.h"

#include "batteryWater.h"

using namespace std;
using namespace Eigen;


enum DIRECTIONS {
	NORTH = 0,
	EAST = 90,
	SOUTH = 180,
	WEST = 270
};


struct LIDAR
{
	bool frontSensor;
	bool backSensor;
	bool leftSensor;
	bool rightSensor;
};

class FlightController
{
private: 
	//LIDAR DATA 	
	LOCATION currentLocation; //currentLocation of drone  //Islam
	LOCATION futureLocation; //expected next Location of Drone
	vector<LOCATION> collisions; //vector of collisions 
	LIDAR lidarData; // will update each iteration and will showcase the collisions that are in the way of drone
	vector<LOCATION> path; //updates the path from current location to destination (Navigation)
	double requestedSpeed; //
	vector<pair<LOCATION, double>> pathHistory; //path that we took as well as time it took
	Vector2d directionOfDrone; //this will be a 2d vector representation

public: 

	//constuctor receives the location of Drone as well as direction in terms of Cardinal Degree
	FlightController(LOCATION locOfDrone, double direction);

	//saving to and reading From files (Collissions and Path History)
	void writeToCollisionDATFile(const vector<LOCATION>& vec);
	void writeToCollisionTXTFile(const vector<LOCATION>& vec);
	bool readCollisionDATFile(); //populates collisions vector with contents of Collision File
	void savePathHistoryDATFile();
	bool readPathHistory(vector<pair<LOCATION, double>>& vec);
	
	//getters and setters
	bool setSpeed(int speed);
	int getRequestedSpeed();
	LOCATION getCurrentLocation(void);
	LOCATION getFutureLocation(void);

	//updateLidarData()
	void updateLidarData(); 
	bool MoveDrone(batteryWater& P);
	double generateLengthOfArc(double Angle, double radius);
	Vector2d getDirectionOfDrone(void);
	bool UpdatePath(vector<LOCATION> path);
};







