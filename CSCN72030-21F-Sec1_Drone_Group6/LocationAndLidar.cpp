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
	Vector3d north(0, 1, 0);
	Vector3d v(vec[0], vec[1], 0);
	double dotProduct = (north.dot(v));
	double scalarProduct = north.norm() * v.norm();
	double angle = acos(dotProduct / scalarProduct) * RADIANS_TO_DEGREES;
	Vector3d crossProduct = north.cross(v);
	if (crossProduct[2] > 0)
	{
		//cout << endl<<"The angle is " << 360-angle << " degress." << endl;
		//cout << "The cross product is " << endl<< crossProduct << endl << endl;
		return 360 - angle;
	}
	else
	{
		//cout << endl << "The angle is " << angle << " degress." << endl;
		//cout << "The cross product is " << endl << crossProduct << endl << endl;
		return angle;
	}
}


inline bool isEqual(double x, double y) {
	const double epsilon = 1e-5;
	return abs(x - y) <= epsilon;
	// see Knuth section 4.2.2 pages 217-218
}

double provideYawAngleBetweenTwoVectors(Vector2d v1, Vector2d v2) //if positive than it is clockwise from first
{
	Vector3d first(v1[0], v1[1], 0);
	Vector3d second(v2[0], v2[1], 0);
	first.normalize();
	second.normalize();
	double dotProduct = first.dot(second);
	double scalarProduct = first.norm() * second.norm();
	double angle = acos(dotProduct / scalarProduct) * RADIANS_TO_DEGREES;
	Vector3d crossProduct = first.cross(second);
	if (crossProduct[2] >= 0)
	{
		//	cout << endl << "The angle is " << -angle << " degress." << endl;
		//	cout << "The cross product is " << endl << crossProduct << endl << endl;
		return -angle;
	}
	else
	{
		//	cout << endl << "The angle is " <<  angle << " degress." << endl;
		//	cout << "The cross product is " << endl << crossProduct << endl << endl;
		return angle;
	}

}

 double generateLengthOfArc(double Angle, double radius)
{
	return Angle * DEGREES_TO_RADIANS * radius;  //ARC is EQUAL TO ANGLE * RADIUS 
}