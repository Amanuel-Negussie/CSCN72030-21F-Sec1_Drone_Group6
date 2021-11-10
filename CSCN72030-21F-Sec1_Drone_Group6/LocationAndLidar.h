#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include "Eigen/Dense"
#include "Coord.h"
#include <numeric>
const double RADIANS_TO_DEGREES = 180 / M_PI;
const double DEGREES_TO_RADIANS = M_PI / 180;

using namespace Eigen;


inline bool isEqual(double x, double y);

struct LOCATION
{
	double x, y;
	void setLocation(double x, double y);
	void setLocation(Coord& loc);
	void setLocation(LOCATION& loc);
	Vector2d getVectorTo(LOCATION loc); //provides a vector from current location to provided location
	double getDistance(LOCATION loc); //returns the distance from one location to other location
};



//helper function for converting direction from cardinal to vector vice/versa 
Vector2d provideVectorFromCardinalDegree(double direction);
double provideCardinalDegreeFromVector(Vector2d vec);