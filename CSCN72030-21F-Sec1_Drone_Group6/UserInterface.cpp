#include "UserInterface.h"

void viewPathHistory(vector<PATH_HISTORY> myVector)
{
	cout << "Path History" << endl;
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

