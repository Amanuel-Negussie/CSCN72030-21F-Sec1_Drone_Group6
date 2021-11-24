#include "Physics.h"




inline bool isEqual(double x, double y) {
	return abs(x - y) <= EPSILON;
}

double generateLengthOfArc(double Angle, double radius)
{
	return Angle * DEGREES_TO_RADIANS * radius;  //ARC is EQUAL TO ANGLE * RADIUS 
}



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

//helper function for converting direction from cardinal to vector vice/versa 

double provideCardinalDegreeBetweenTwoVectors(Vector2d v1, Vector2d v2) //if positive than it is clockwise from first
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


string provideCardinalName(double angle)
{
	if (isEqual(angle, 0))
	{
		return "NORTH";
	}
	else if (isEqual(angle, 90))
	{
		return "EAST";
	}
	else if (isEqual(angle, 180))
	{
		return "SOUTH";
	}
	else if (isEqual(angle, 270))
	{
		return "WEST";
	}
	else
		return to_string(angle);

}