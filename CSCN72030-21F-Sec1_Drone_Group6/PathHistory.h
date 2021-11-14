#pragma once
#include "Location.h"
#include <string>

using namespace std;

struct PATH_HISTORY
{
	LOCATION location;
	double duration;
	string direction;
}typedef PATH_HISTORY;