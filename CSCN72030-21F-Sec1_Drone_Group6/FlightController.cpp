#include "FlightController.h"

//private functions 



//constructor

FlightController::FlightController(LOCATION locOfDrone, double direction)
{
	currentLocation.setLocation(locOfDrone);
	directionOfDrone = provideVectorFromCardinalDegree(direction);
	futureLocation.setLocation(currentLocation);
	lidarData.frontSensor = false;
	lidarData.backSensor = false;
	lidarData.leftSensor = false;
	lidarData.rightSensor = false;
}


//private functions
void FlightController::updateLidarData()
{

}


Vector2d FlightController::provideVectorFromCardinalDegree(double direction) //helper function stub that converts direction in degree to vector
{
	return Vector2d(0, 1); //only shows north for now
}



//public functions
//getters and setters 


bool FlightController::setSpeed(int speed)
{
	requestedSpeed = speed;
}
int FlightController:: getSpeed()
{
	return requestedSpeed;
}

LOCATION FlightController::getCurrentLocation(void)
{
	return currentLocation;
}

LOCATION FlightController::getFutureLocation(void)
{
	return futureLocation;
}
Vector2d FlightController:: getDirectionOfDrone(void)
{
	return directionOfDrone;
}





//updatePath, MoveDrone and updatePathHistory


bool FlightController:: updatePath(vector<LOCATION> path) //updates path that the drone must follow
{
	return true;
}

bool FlightController::MoveDrone(batteryWater& P)
{
	//future location will always be first thing in vector
	futureLocation = path.at(0);
	if (lidarData.frontSensor)
	{
		return false;
	}
	else
		//Move the drone and drain battery
	{
		currentLocation = futureLocation;
		path.erase(path.begin()); //erase the first element in the vector to let the next element be first
		return true;

	}
}

bool updatePathHistory(vector<pair<LOCATION, double>>& vec) //updates Path History
{
	return true;
}


//READING AND WRITING TO FILE COLLISIONS AND PATH HISTORY 


//saving to and reading From files (Collissions and Path History)
void FlightController:: writeToCollisionDATFile(const vector<LOCATION>& vec)
{

}
void FlightController:: writeToCollisionTXTFile(const vector<LOCATION>& vec)
{

}
void FlightController::  writeToPathHistoryDATFile()
{

}
void FlightController:: writeToPathHistoryTXTFile()
{

}
bool FlightController:: readCollisionDATFile() //populates collisions vector with contents of Collision File
{
	return true;
}
bool FlightController:: readPathHistoryDATFile() //populates pathHistory vector with contents from PathHistoryFile
{
	return true;
}


