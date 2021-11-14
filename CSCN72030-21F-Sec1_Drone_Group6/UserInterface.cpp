#include "UserInterface.h"

void viewPathHistory(vector<PATH_HISTORY> myVector)
{
	cout << "LOCATION\t\tDURATION\tDIRECTION\t\n";
	for (auto i : myVector)
	{
		cout << i.location.x << "\ty: " << i.location.y << "\tDuration: " << fixed << setprecision(2) << i.duration << "\tseconds.\t Direction: " << i.direction << endl;
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

