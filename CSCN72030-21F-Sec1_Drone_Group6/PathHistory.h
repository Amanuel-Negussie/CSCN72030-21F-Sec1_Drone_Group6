#pragma once
#include "Location.h"
#include <string>

using namespace std;

struct PATH_HISTORY
{
	LOCATION location;
	double duration;
	string direction;
	double speed;
	int power;
}typedef PATH_HISTORY;