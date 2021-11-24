#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <string>


//#include <numeric>
#include "Eigen/Dense"
const double RADIANS_TO_DEGREES = 180 / M_PI;
const double DEGREES_TO_RADIANS = M_PI / 180;
const double EPSILON = 1e-5;

using namespace Eigen;
using namespace std;


inline bool isEqual(double x, double y);
double generateLengthOfArc(double Angle, double radius);

//helper function for converting direction from cardinal to vector vice/versa 
Vector2d provideVectorFromCardinalDegree(double direction);
double provideCardinalDegreeFromVector(Vector2d vec);
double provideCardinalDegreeBetweenTwoVectors(Vector2d v1, Vector2d v2); //if positive than it is clockwise from first

string provideCardinalName(double angle);