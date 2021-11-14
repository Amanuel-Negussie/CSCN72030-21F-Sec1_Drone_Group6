#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "Eigen/Dense"
#include "Location.h"
#include "PathHistory.h"

using namespace std;

//Flight Controlelr Module 
//outside in the main or user interface
double calculateTotalTime(vector<PATH_HISTORY> myVector);
void viewPathHistory(vector<PATH_HISTORY> myVector);
string provideCardinalName(double angle);




