#include "LocationAndLidar.h"


void LOCATION::setLocation(double x, double y)
{
	this->x = x;
	this->y = y;
}

void LOCATION::setLocation(Coord& loc)
{
	this->x = loc.getX();
	this->y = loc.getY();
}

void LOCATION::setLocation(LOCATION& loc)
{
	this->x = loc.x;
	this->y = loc.y;
}

Vector2d LOCATION::getVectorTo(LOCATION loc) //provides a vector from current location to provided location
{
	return Vector2d(loc.x - this->x, loc.y - this->y);
}


double LOCATION::getDistance(LOCATION loc) //returns the distance from one location to other location
{
	return sqrt((this->x - loc.x) * (this->x - loc.x) + (this->y - loc.y) * (this->y - loc.y));
}


//helper function for converting direction from cardinal to vector vice/versa 
Vector2d provideVectorFromCardinalDegree(double angle)
{
	double x = sin(angle * DEGREES_TO_RADIANS);
	if (isEqual(x, 0))
		x = 0;
	double y = cos(angle * DEGREES_TO_RADIANS);
	if (isEqual(y, 0))
		y = 0;
	Vector2d v(x, y);
	v.normalize();
	return v;

}


double provideCardinalDegreeFromVector(Vector2d vec)
{
	return 1;
}


inline bool isEqual(double x, double y) {
	const double epsilon = 1e-5;
	return abs(x - y) <= epsilon;
	// see Knuth section 4.2.2 pages 217-218
}

