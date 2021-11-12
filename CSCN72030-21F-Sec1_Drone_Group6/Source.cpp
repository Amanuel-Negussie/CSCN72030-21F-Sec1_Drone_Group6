
#include <iostream>
#include "batteryWater.h"
#include "FlightController.h"
#include "NavSensor.h"

int main() {
	std::cout << "Hello, World!" << std::endl;
	//connection* connect = new connection((char*) "A1", (char*) "a2");


	Coord startingLocation(0, 0);
	FlightController myFC = FlightController(startingLocation, WEST);
    batteryWater bW;
    vector<LOCATION> myWritingVector;
    LOCATION thisVector;
    for (int i = 0; i < 20; i++)
    {

        thisVector.setLocation(9, rand() % 10);
        myWritingVector.push_back(thisVector);
    }

    //   myFC.writeToCollisionFile(myWritingVector); //
    myFC.readCollisionDATFile();
    myFC.writeToCollisionTXTFile(myWritingVector);
    vector<LOCATION> coolPath;
    LOCATION coolLoc;
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < 10; j++)
            {
                coolLoc.setLocation(i, j);
                cout << coolLoc.x << endl << coolLoc.y << endl;
                coolPath.push_back(coolLoc);
            }
        }
        else
        {
            for (int j = 9; j >= 0; j--)
            {
                coolLoc.setLocation(i, j);
                cout << coolLoc.x << endl << coolLoc.y << endl;
                coolPath.push_back(coolLoc);
            }
        }
    }


    while (myFC.MoveDrone(bW))
    {
        cout << "LOCATION: " << myFC.getCurrentLocation().x << "," << myFC.getCurrentLocation().y <<
            "\tDrone Power: " << bW.getCurrentBattery() << " Watts" << endl;
    }




    myFC.writeToPathHistoryDATFile();
    myFC.writeToPathHistoryTXTFile();
    vector<pair<LOCATION, double>> myPathHistory;
    myFC.writeToPathHistoryDATFile();
    myFC.readPathHistoryDATFile();

    cout << "The total time it took to get to final destination is " << calculateTotalTime(myPathHistory) << " seconds." << endl;
    cout << "HERE IS THE FLIGHT PATH HISTORY " << endl;
    viewPathHistory(myPathHistory);
	return 0;
}