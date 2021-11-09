#pragma once

#include "Eigen/Dense"
using namespace Eigen;

struct LOCATION
{
	double x, y;
	void setLocation(double x, double y);
	void setLocation(LOCATION loc);
	Vector2d getVectorTo(LOCATION loc); //provides a vector from current location to provided location
	double getDistance(LOCATION loc); //returns the distance from one location to other location
};



