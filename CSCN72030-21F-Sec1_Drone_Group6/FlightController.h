#pragma once

#include <vector>
#include <math.h>
#include <Eigen/Dense>
#include <numeric>

#include "LocationAndLidar.h"
#include "batteryWater.h"

using namespace std;
using namespace Eigen;

#define COLLISIONS_DAT_FILENAME "Collisions.dat"
#define COLLISIONS_TXT_FILENAME "Collisions.txt"
#define PATH_HISTORY_DAT_FILENAME "PathHistory.dat"
#define PATH_HISTORY_TXT_FILENAME "PathHistory.txt"
#define MASS_DRONE 21.1
#define ACC_OF_GRAVITY -9.8
#define ALTITUDE 4.572 //15 feet to meters
#define RADIUS 0.41
#define GIVEN_SPEED 5
#define AIR_DENSITY_CONSTANT_K 22.35
#define WATTS 1.037

const double POWER_TO_HOVER = AIR_DENSITY_CONSTANT_K * sqrt(MASS_DRONE * MASS_DRONE * MASS_DRONE) / RADIUS;


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
	vector<LOCATION> collisionList; //vector of collisions 
	LIDAR lidarData; // will update each iteration and will showcase the collisions that are in the way of drone
	vector<LOCATION> path; //updates the path from current location to destination (Navigation)
	double speed; //
	vector<pair<LOCATION, double>> pathHistory; //path that we took as well as time it took
	Vector2d directionOfDrone; //this will be a 2d vector representation

	//Interface with Navigation


	//updateLidarData
	void updateLidarData();
	



public: 

	//constuctor receives the location of Drone as well as direction in terms of Cardinal Degree
	FlightController(Coord& locOfDrone, double direction);
	
	//getters and setters
	bool setSpeed(double speed);
	double getSpeed();
	LOCATION getCurrentLocation(void);
	LOCATION getFutureLocation(void);
	void setCurrentLocation(Coord& coord); 
	void setFutureLocation(Coord& coord); 
	Vector2d getDirectionOfDrone(void);

	//Update Path and Move Drone
	bool updatePath(vector<LOCATION> path); //updates path that the drone must follow
	bool MoveDrone(batteryWater* P); //moves drone unless there's an obstacle in the way
	bool updatePathHistory(vector<pair<LOCATION, double>>& vec); //updates Path History
	vector<pair<LOCATION, double>> getPathHistory();

	//Navigation Interface 
	bool MoveDrone_Once(Coord& coord, batteryWater& P); //Islams


	//saving to and reading From files (Collissions and Path History)
	void writeToCollisionDATFile(const vector<LOCATION>& vec);
	void writeToCollisionTXTFile(const vector<LOCATION>& vec);
	void writeToPathHistoryDATFile();
	void writeToPathHistoryTXTFile();
	bool readCollisionDATFile(); //populates collisions vector with contents of Collision File
	bool readPathHistoryDATFile(); //populates pathHistory vector with contents from PathHistoryFile
};


//outside
double calculateTotalTime(vector<pair<LOCATION, double>> myVector);
void viewPathHistory(vector<pair<LOCATION, double>> myVector);




