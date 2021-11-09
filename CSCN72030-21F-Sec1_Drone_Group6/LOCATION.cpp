#include "Location.h"

void LOCATION::setLocation(double x, double y)
{
	this->x = x;
	this->y = y;
}

void LOCATION::setLocation(LOCATION loc)
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
