#include "FlightController.h"


//constructor

FlightController::FlightController(Coord& locOfDrone, double direction)
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
	double angle = provideCardinalDegreeFromVector(directionOfDrone);
	if (angle == NORTH)
		//north 
	{
		for (const auto& i : collisionList)
		{
			if (currentLocation.x == i.x && currentLocation.y + 1 == i.y) //NORTH
				lidarData.frontSensor = true;
			if (currentLocation.x + 1 == i.x && currentLocation.y == i.y) //EAST
				lidarData.rightSensor = true;
			if (currentLocation.x - 1 == i.x && currentLocation.y == i.y) //WEST 
				lidarData.leftSensor = true;
			if (currentLocation.x == i.x && currentLocation.y - 1 == i.y) //SOUTH
				lidarData.backSensor = true;
		}
	}
	else if (angle == EAST)
	{
		for (const auto& i : collisionList)
		{
			if (currentLocation.x == i.x && currentLocation.y + 1 == i.y)  // NORTH  left
				lidarData.leftSensor = true;
			if (currentLocation.x + 1 == i.x && currentLocation.y == i.y) // EAST front
				lidarData.frontSensor = true;
			if (currentLocation.x - 1 == i.x && currentLocation.y == i.y) //WEST back
				lidarData.backSensor = true;
			if (currentLocation.x == i.x && currentLocation.y - 1 == i.y) // SOUTH right
				lidarData.rightSensor = true;
		}
	}
	else if (angle == WEST)
	{
		for (const auto& i : collisionList)
		{
			if (currentLocation.x == i.x && currentLocation.y + 1 == i.y)  // NORTH  right
				lidarData.rightSensor = true;
			if (currentLocation.x + 1 == i.x && currentLocation.y == i.y) //EAST back
				lidarData.backSensor = true;
			if (currentLocation.x - 1 == i.x && currentLocation.y == i.y) //WEST front
				lidarData.frontSensor = true;
			if (currentLocation.x == i.x && currentLocation.y - 1 == i.y) // SOUTH left
				lidarData.leftSensor = true;
		}
	}
	else if (angle == SOUTH)
	{
		for (const auto& i : collisionList)
		{
			if (futureLocation.x == i.x && currentLocation.y + 1 == i.y)  // NORTH  back
				lidarData.backSensor = true;
			if (currentLocation.x + 1 == i.x && currentLocation.y == i.y) //EAST left
				lidarData.leftSensor = true;
			if (currentLocation.x - 1 == i.x && currentLocation.y == i.y) //WEST right
				lidarData.rightSensor = true;
			if (currentLocation.x == i.x && currentLocation.y - 1 == i.y) // SOUTH front
				lidarData.frontSensor = true;
		}
	}
}




//public functions
//getters and setters 


bool FlightController::setSpeed(double speed)
{
	if (speed > 0 && speed < 20)
	{
		this->speed = speed;
		return true;
	}
	else
		return false;
}


double FlightController:: getSpeed()
{
	return speed;
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


// Interface Requirements for setting location through Coord 
void FlightController:: setCurrentLocation(Coord& coord)
{
	this->currentLocation.x = coord.getX();
	this->currentLocation.y = coord.getY();
}

void FlightController:: setFutureLocation(Coord& coord)
{
	this->futureLocation.x = coord.getX();
	this->futureLocation.y = coord.getY();

}

//updatePath, MoveDrone and updatePathHistory


bool FlightController:: updatePath(vector<LOCATION> path) //updates path that the drone must follow
{
	this->path = path;
	return true;
}

bool FlightController::MoveDrone(batteryWater* P)
{
	//get future location from path 
	//futureLocation = path.at(0);
	Vector2d intendedDirection = currentLocation.getVectorTo(futureLocation);
	double yawAngle = provideYawAngleBetweenTwoVectors(directionOfDrone, intendedDirection);

	if (isnan(yawAngle))
		yawAngle = 0;
	double yawDuration = abs(generateLengthOfArc(yawAngle, RADIUS)) / speed; //distance over speed equals time
	//Power = F * distance/ time 
	//Power = mg*height /time 
	double yawPowerLost(0);
	if (yawDuration != 0)
	{
		yawPowerLost = CONSTANT_FACTOR_TEN * yawDuration;
		P->decreaseBattery(yawPowerLost);
	}
	if (currentLocation.getDistance(futureLocation) != 0)
		directionOfDrone = intendedDirection;
	updateLidarData();
	double angle = provideCardinalDegreeFromVector(directionOfDrone);
	if (isnan(angle))
		angle = 0;
	double movePowerLost(0);
	if (!lidarData.frontSensor)
	{
		double timeDuration = abs(currentLocation.getDistance(futureLocation)) / speed; //create real calculation 
		if (isnan(timeDuration))
			timeDuration = 0;
		if (timeDuration != 0)
		{
			movePowerLost = CONSTANT_FACTOR_TEN * timeDuration;
			P->decreaseBattery(movePowerLost);
		}
		pathHistory.push_back(make_pair(futureLocation, timeDuration + yawDuration));
		currentLocation = futureLocation;
		//path.erase(path.begin());
		return true;
	}
	else
	{
		pathHistory.push_back(make_pair(currentLocation, yawDuration));
		return false;
	}
}

bool FlightController::updatePathHistory(vector<pair<LOCATION, double>>& vec) //updates Path History
{
	
	return true;
}


//Move Drone Once
bool FlightController::MoveDrone_Once(Coord& coord, batteryWater& P)
{
	futureLocation.setLocation(coord);
	Vector2d intendedDirection = currentLocation.getVectorTo(futureLocation); //get the intended direction of the Drone

	double yawAngle = provideYawAngleBetweenTwoVectors(directionOfDrone, intendedDirection);
	if (isnan(yawAngle))
		yawAngle = 0;
	double yawDuration = abs(generateLengthOfArc(yawAngle, RADIUS)) / speed; //distance over speed equals time
	//Power = F * distance/ time 
	//Power = mg*height /time 
	double yawPowerLost(0);
	if (yawDuration != 0)
	{
		yawPowerLost = CONSTANT_FACTOR_TEN * yawDuration;
		P.decreaseBattery(yawPowerLost);
	}
	if (currentLocation.getDistance(futureLocation) != 0)
		directionOfDrone = intendedDirection;
	updateLidarData();
	double angle = provideCardinalDegreeFromVector(directionOfDrone);
	if (isnan(angle))
		angle = 0;
	double movePowerLost(0);
	if (!lidarData.frontSensor)
	{
		double timeDuration = abs(currentLocation.getDistance(futureLocation)) / speed; //create real calculation 
		if (isnan(timeDuration))
			timeDuration = 0;
		if (timeDuration != 0)
		{
			movePowerLost = CONSTANT_FACTOR_TEN * timeDuration;
			P.decreaseBattery(movePowerLost);
		}
		pathHistory.push_back(make_pair(futureLocation, timeDuration + yawDuration));
		currentLocation = futureLocation;
		path.erase(path.begin());
		return true;
	}
	else
	{
		pathHistory.push_back(make_pair(currentLocation, yawDuration));
		return false;
	}
}


//READING AND WRITING TO FILE COLLISIONS AND PATH HISTORY 


//saving to and reading From files (Collissions and Path History)
void FlightController:: writeToCollisionDATFile(const vector<LOCATION>& vec)
{
	ofstream os(COLLISIONS_DAT_FILENAME, ios::out | ios::binary);
	typename vector<LOCATION>::size_type size = vec.size();
	os.write((char*)&size, sizeof(size));
	os.write((char*)&vec[0], (vec.size() * sizeof(LOCATION)));
	os.close();
}



void FlightController:: writeToCollisionTXTFile(const vector<LOCATION>& vec)
{
	ofstream os(COLLISIONS_TXT_FILENAME, ios::out);
	os << "LIST OF COLLISIONS" << endl;
	int count = 0;
	for (auto i : vec)
	{
		os << ++count << ".\tx: " << i.x << "\ty: " << i.y << "\n";
	}
	os.close();
}
void FlightController::  writeToPathHistoryDATFile()
{
	ofstream os(PATH_HISTORY_DAT_FILENAME, ios::out | ios::binary);
	typename vector<pair<LOCATION,double>>::size_type size = pathHistory.size();
	os.write((char*)&size, sizeof(size));
	os.write((char*)&pathHistory[0], (pathHistory.size() * sizeof(pair<LOCATION,double>)));
	os.close();
}
void FlightController:: writeToPathHistoryTXTFile()
{

	ofstream os(PATH_HISTORY_TXT_FILENAME, ios::out);
	os << "Path History" << endl;
	int count = 0;
	for (auto i : pathHistory)
	{
		os << ++count << ".\tx: " << i.first.x << "\ty: " << i.first.y << "\tDuration: " << fixed<<setprecision(2)<< i.second << "\tseconds.\n";
	}
	os.close();
}
bool FlightController:: readCollisionDATFile() //populates collisions vector with contents of Collision File
{
	ifstream is(COLLISIONS_DAT_FILENAME, ios::in | ios::binary);
	if (!is.is_open())
		return false;
	typename vector<LOCATION>::size_type size = 0;
	is.read((char*)&size, sizeof(size));
	collisionList.resize(size);
	is.read((char*)&collisionList[0], collisionList.size() * sizeof(LOCATION));
	is.close();
	return true;
}
bool FlightController:: readPathHistoryDATFile() //populates pathHistory vector with contents from PathHistoryFile
{
	ifstream is(PATH_HISTORY_DAT_FILENAME, ios::in | ios::binary);
	if (!is.is_open())
		return false;
	typename vector<pair<LOCATION,double>>::size_type size = 0;
	is.read((char*)&size, sizeof(size));
	pathHistory.resize(size);
	is.read((char*)&pathHistory[0], pathHistory.size() * sizeof(pair<LOCATION,double>));
	is.close();
	return true;
}

vector<pair<LOCATION, double>> FlightController::getPathHistory()
{
	return pathHistory;
}

void viewPathHistory(vector<pair<LOCATION, double>> myVector)
{
	for (auto i : myVector)
	{
		cout << "(" << i.first.x << "," << i.first.y << ")\tTime: " << i.second << " s" << endl;
	}
}


double calculateTotalTime(vector<pair<LOCATION, double>> myVector)
{
	double totalTime(0);

	for (auto i : myVector)
	{
		totalTime += i.second;
	}
	return totalTime;
}
