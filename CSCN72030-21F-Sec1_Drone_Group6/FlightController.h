#pragma once

#include <vector>
#include <math.h>
#include <Eigen/Dense>
#include <numeric>

#include "LocationAndLidar.h"
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

	//updateLidarData
	void updateLidarData();
	



public: 

	//constuctor receives the location of Drone as well as direction in terms of Cardinal Degree
	FlightController(Coord& locOfDrone, double direction);
	
	//getters and setters
	bool setSpeed(int speed);
	int getSpeed();
	LOCATION getCurrentLocation(void);
	LOCATION getFutureLocation(void);
	Vector2d getDirectionOfDrone(void);



	//Update Path and Move Drone
	bool updatePath(vector<LOCATION> path); //updates path that the drone must follow
	bool MoveDrone(batteryWater& P); //moves drone unless there's an obstacle in the way
	bool updatePathHistory(vector<pair<LOCATION, double>>& vec); //updates Path History

	//saving to and reading From files (Collissions and Path History)
	void writeToCollisionDATFile(const vector<LOCATION>& vec);
	void writeToCollisionTXTFile(const vector<LOCATION>& vec);
	void writeToPathHistoryDATFile();
	void writeToPathHistoryTXTFile();
	bool readCollisionDATFile(); //populates collisions vector with contents of Collision File
	bool readPathHistoryDATFile(); //populates pathHistory vector with contents from PathHistoryFile


};







