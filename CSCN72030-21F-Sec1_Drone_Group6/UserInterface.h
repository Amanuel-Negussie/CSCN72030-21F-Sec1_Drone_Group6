#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "Eigen/Dense"
#include "Location.h"
#include "PathHistory.h"
#include "Lidar.h"

using namespace std;

//Flight Controller Module 
//outside in the main or user interface
double calculateTotalTime(vector<PATH_HISTORY> myVector);
void viewPathHistory(vector<PATH_HISTORY> myVector);
void viewCollisions(vector<LOCATION> vec);
string outputLidarData(LIDAR lid); 


string provideCardinalName(double angle);




