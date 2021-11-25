#include "UserInterface.h"

void viewPathHistory(vector<PATH_HISTORY> myVector)
{
	cout << "Drone's Movement History" << endl;
	cout << "#\tLOCATION\tDURATION\tDIRECTION\tSPEED\t\tPOWER\n";
	int count(0);
	for (auto i : myVector)
	{
		cout << ++count << ".\t(" << fixed<<setprecision(2)<< i.location.x << "," << fixed<<setprecision(2)<< i.location.y << ")\t" 
			<< fixed << setprecision(2) << i.duration << " s\t\t" << i.direction << "\t\t" << i.speed << " m/s\t" << i.power << " W" << endl;
	}
}


double calculateTotalTime(vector<PATH_HISTORY> myVector)
{
	double totalTime(0);

	for (auto i : myVector)
	{
		totalTime += i.duration;
	}
	return totalTime;
}


//write a collision vector a file with name 



void viewCollisions(vector<LOCATION> vec)
{
	cout <<endl<< "LIST OF COLLISIONS" << endl;
	int count = 0;
	for (auto i : vec)
	{
		cout << ++count << ".\tx: " << i.x << "\ty: " << i.y << endl;
	}
	
}

string outputLidarData(LIDAR lid)
{
	string s; 
	s.append("FRONT SENSOR: ");
	s.append(lid.frontSensor ? "OBJECT DETECTED" : "                ");
	s.append("\nLEFT SENSOR: ");
	s.append(lid.leftSensor ? "OBJECT DETECTED" : "                 ");
	s.append("\nRIGHT SENSOR: ");
	s.append(lid.rightSensor ? "OBJECT DETECTED" : "                "); 
	s.append("\nBACK SENSOR: ");
	s.append(lid.backSensor ? "OBJECT DETECTED" : "                 ");
	return s;
}

