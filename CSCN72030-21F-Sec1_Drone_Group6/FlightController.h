#pragma once

#include <vector>
#include <math.h>
#include <Eigen/Dense>
#include <numeric>
#include <iomanip>
#include "Alert.h"
#include "Physics.h"
#include "Location.h"
#include "Lidar.h"
#include "PathHistory.h"
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
#define YAW_SPEED 3
#define CONSTANT_FACTOR_TEN 12
#define DECCELERATION_RATE -1
#define ACCELERATION_RATE 0.5

const double POWER_TO_HOVER = AIR_DENSITY_CONSTANT_K * sqrt(MASS_DRONE * MASS_DRONE * MASS_DRONE) / RADIUS;


enum DIRECTIONS {
	NORTH = 0,
	EAST = 90,
	SOUTH = 180,
	WEST = 270
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
	double requestedSpeed;
	vector<PATH_HISTORY> pathHistory; //path that we took as well as time it took
	Vector2d directionOfDrone; //this will be a 2d vector representation
	void updateLidarData(); //this constantly happens when Move() function occurs
	void moveDroneYaw(batteryWater* P, double& yawDuration); //this is a helper function to Move that rotates the drone in the yaw updating the yaw duration
	void moveDronePitch(batteryWater* P, double& pitchDuration); //this is a helper function that also Moves the drone in the pitch updating the pitch duration
	void decellerateDrone(batteryWater* P, double& duration);
	void accelerateDrone(batteryWater* P, double& duration);
public: 

	//constuctor receives the location of Drone as well as direction in terms of Cardinal Degree
	FlightController(Coord locOfDrone, double direction);
	double getSpeed(); 
	double getRequestedSpeed(); //this is for the user to control
	bool setRequestedSpeed(double); // this is for the user to control
	LOCATION getCurrentLocation(void);
	LOCATION getFutureLocation(void);
	void setCurrentLocation(Coord coord); 
	void setFutureLocation(Coord coord); 
	Vector2d getDirectionOfDrone(void);

	//Move Drone
	bool MoveDrone(batteryWater* P); //moves drone unless there's an obstacle in the way
	vector<PATH_HISTORY> getPathHistory();

	//Navigation Interface


	//saving to and reading From files (Collissions and Path History)
	void writeToCollisionDATFile(const vector<LOCATION>& vec);
	void writeToCollisionTXTFile(const vector<LOCATION>& vec);
	void writeToPathHistoryDATFile();
	void writeToPathHistoryTXTFile();
	bool readCollisionDATFile(); //populates collisions vector with contents of Collision File
	bool readPathHistoryDATFile(); //populates pathHistory vector with contents from PathHistoryFile
};



//helper function for converting direction from cardinal to vector vice/versa 
Vector2d provideVectorFromCardinalDegree(double direction);
double provideCardinalDegreeFromVector(Vector2d vec);
double provideCardinalDegreeBetweenTwoVectors(Vector2d v1, Vector2d v2); //if positive than it is clockwise from first
double generateLengthOfArc(double Angle, double radius);



