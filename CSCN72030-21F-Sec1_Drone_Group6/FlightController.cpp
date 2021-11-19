#include "FlightController.h"


//constructor

FlightController::FlightController(Coord locOfDrone, double direction)
{
	currentLocation.setLocation(locOfDrone);
	directionOfDrone = provideVectorFromCardinalDegree(direction);
	futureLocation.setLocation(currentLocation);
	lidarData.frontSensor = false;
	lidarData.backSensor = false;
	lidarData.leftSensor = false;
	lidarData.rightSensor = false;
	requestedSpeed = GIVEN_SPEED;
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

void FlightController::moveDroneYaw(batteryWater* P, double& yawDuration)
{
	//know how much Yaw you must turn 
	Vector2d intendedDirection = currentLocation.getVectorTo(futureLocation);
	double yawAngle = provideCardinalDegreeBetweenTwoVectors(directionOfDrone, intendedDirection);

	if (isnan(yawAngle))
		yawAngle = 0;

	yawDuration = abs(generateLengthOfArc(yawAngle, RADIUS)) / YAW_SPEED; //distance over speed equals time
	if (isnan(yawDuration))
		yawDuration = 0;
	if (yawDuration != 0)
	{
		P->decreaseBattery(CONSTANT_FACTOR_TEN * yawDuration); //this is the rotation spin 
	}
	if (currentLocation.getDistance(futureLocation) != 0) //if current Location is not the same as future then change direction.
		directionOfDrone = intendedDirection;

}

//moving the Drone forward
void FlightController::moveDronePitch(batteryWater* P, double& pitchDuration)
{
	pitchDuration = abs(currentLocation.getDistance(futureLocation)) / requestedSpeed; //create real calculation 
	if (isnan(pitchDuration))
		pitchDuration = 0;
	if (pitchDuration != 0)
	{

		accelerateDrone(P, pitchDuration);
		
	}
}

//slowing down drone to speed 0
void FlightController::decellerateDrone(batteryWater* P, double& duration) //calculate the duration to decellerate the drone
{
	duration = 2 * (currentLocation.getDistance(futureLocation)) / requestedSpeed; //time = 2*displacement/(final velocity + initial velocity)
	P->decreaseBattery(CONSTANT_FACTOR_TEN * duration);
	speed = 0;
}

//ramping up drone to requested speed
void FlightController::accelerateDrone(batteryWater* P, double& duration)
{
	duration = 2 * (currentLocation.getDistance(futureLocation)) / (requestedSpeed + speed); //time = 2*displacement/(final velocity + initial velocity)
	//P->decreaseBattery(CONSTANT_FACTOR_TEN * duration);
	P->decreaseBattery(CONSTANT_FACTOR_TEN);// Dannys modification
	speed = requestedSpeed;
}


//public functions
//getters and setters 


bool FlightController::setRequestedSpeed(double speed)
{
	if (speed > 0 && speed < 20)
	{
		requestedSpeed = speed;
		return true;
	}
	else
		return false;
}

double FlightController::getRequestedSpeed()
{
	return requestedSpeed;
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
void FlightController:: setCurrentLocation(Coord coord)
{
	this->currentLocation.x = coord.getX();
	this->currentLocation.y = coord.getY();
}

void FlightController:: setFutureLocation(Coord coord)
{
	this->futureLocation.x = coord.getX();
	this->futureLocation.y = coord.getY();

}

vector<LOCATION> FlightController::getCollisionList()
{
	return collisionList;
}


bool FlightController::MoveDrone(batteryWater* P)
{

	//moveDrone in Yaw 
	double yawDuration(0);
	moveDroneYaw(P,yawDuration);

	//after direction is in intended direction: we're going to check the lidar sensor 
	updateLidarData();


	if (!lidarData.frontSensor) //if false means we can move 
	{

		double pitchDuration(0);
		moveDronePitch(P, pitchDuration);


	
		PATH_HISTORY p;
		p.location = futureLocation;
		p.duration = pitchDuration + yawDuration;
		p.direction = provideCardinalName(provideCardinalDegreeFromVector(directionOfDrone));
		p.speed = speed;
		p.power = P->getCurrentBattery();
		pathHistory.push_back(p);
		return true;
	}
	else // if true means we must hover 
	{
		Alert a = Alert(100); //sending an alert that object is detected 
		double hoverDuration(0);
		decellerateDrone(P, hoverDuration);

		PATH_HISTORY p;
		p.location = currentLocation;
		p.duration = yawDuration + hoverDuration;
		p.direction = provideCardinalName(provideCardinalDegreeFromVector(directionOfDrone));
		p.speed = speed;
		p.power = P->getCurrentBattery();
		pathHistory.push_back(p);

		return false;
	}
}



vector<PATH_HISTORY> FlightController::getPathHistory()
{
	return pathHistory;
}


//READING AND WRITING TO FILE COLLISIONS AND PATH HISTORY


//saving to and reading From files (Collissions and Path History)

bool FlightController:: readCollisionDATFile(string fileName) //populates collisions vector with contents of Collision File
{
	ifstream is(fileName, ios::in | ios::binary);
	if (!is.is_open())
		return false;
	typename vector<LOCATION>::size_type size = 0;
	is.read((char*)&size, sizeof(size));
	collisionList.resize(size);
	is.read((char*)&collisionList[0], collisionList.size() * sizeof(LOCATION));
	is.close();
	return true;

}
bool FlightController:: readPathHistoryDATFile(string fileName) //populates pathHistory vector with contents from PathHistoryFile
{
	ifstream is(fileName, ios::in | ios::binary);
	if (!is.is_open())
		return false;
	typename vector<PATH_HISTORY>::size_type size = 0;
	is.read((char*)&size, sizeof(size));
	pathHistory.resize(size);
	is.read((char*)&pathHistory[0], pathHistory.size() * sizeof(pair<LOCATION,double>));
	is.close();
	return true;


}


//WRITING VECTORS TO FILE WITH GIVEN FILE NAME 
bool writeCollisionToDATFile(const vector<LOCATION> vec, string fileName)
{
	ofstream os(fileName, ios::out | ios::binary);
	if (!os.is_open())
		return false;
	typename vector<LOCATION>::size_type size = vec.size();
	os.write((char*)&size, sizeof(size));
	os.write((char*)&vec[0], (vec.size() * sizeof(LOCATION)));
	os.close();
	return true;
}

bool writeCollisionToTXTFile(const vector<LOCATION> vec, string fileName)
{
	ofstream os(fileName, ios::out);
	if (!os.is_open())
		return false;
	os << "LIST OF COLLISIONS" << endl;
	int count = 0;
	for (auto i : vec)
	{
		os << ++count << ".\tx: " << i.x << "\ty: " << i.y << endl;
	}
	os.close();
	return true;

}

//write Path History 

//writing PathHistory to File 
bool writePathHistoryToDATFile(const vector<PATH_HISTORY> vec, string fileName)
{
	ofstream os(fileName, ios::out | ios::binary);
	if (!os.is_open())
		return false;
	typename vector<PATH_HISTORY>::size_type size = vec.size();
	os.write((char*)&size, sizeof(size));
	os.write((char*)&vec[0], (vec.size() * sizeof(PATH_HISTORY)));
	os.close();
	return true;
}

bool writePathHistoryToTXTFile(const vector<PATH_HISTORY> vec, string fileName)
{
	ofstream os(fileName, ios::out);
	if (!os.is_open())
		return false;
	os << "Path History" << endl;
	os << "#\tLOCATION\tDURATION\tDIRECTION\tSPEED\t\tPOWER\n";
	int count(0);
	for (auto i : vec)
	{
		os << ++count << ".\t(" << fixed << setprecision(2) << i.location.x << "," << fixed << setprecision(2) << i.location.y << ")\t"
			<< fixed << setprecision(2) << i.duration << " s\t\t" << i.direction << "\t\t" << i.speed << " m/s\t" << i.power << " W" << endl;
	}
	os.close();
	return true;
}

