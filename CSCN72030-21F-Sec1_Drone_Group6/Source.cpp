
#include <iostream>
#include "batteryWater.h"
#include "FlightController.h"
#include "NavSensor.h"

int main() {
	std::cout << "Hello, World!" << std::endl;
	connection* connect = new connection((char*) "A1", (char*) "a2");


	Coord startingLocation(0, 0);
	FlightController myFC = FlightController(startingLocation, WEST);
    batteryWater* bW = new batteryWater();
    vector<Coord> myWritingVector;
    for (int i = 0; i < 20; i++)
    {
        Coord thisVector(9, rand() % 10);
        myWritingVector.push_back(thisVector);
    }

   // myFC.writeToCollisionDATFile(myWritingVector); //
    myFC.readCollisionDATFile();
   // myFC.writeToCollisionTXTFile(myWritingVector);
    vector<Coord> coolPath;
    Coord coolLoc;
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < 10; j++)
            {
                coolLoc.setCoord(i, j);
                cout << coolLoc.getX() << endl << coolLoc.getY() << endl;
                coolPath.push_back(coolLoc);
            }
        }
        else
        {
            for (int j = 9; j >= 0; j--)
            {
                coolLoc.setCoord(i, j);
                cout << coolLoc.getX() << endl << coolLoc.getY() << endl;
                coolPath.push_back(coolLoc);
            }
        }
    }


    for (Coord& loc : coolPath)
    {
        myFC.setFutureLocation(loc);
        if(!myFC.MoveDrone(bW))
        {       
            break;
        }
        else
        {
            cout << "LOCATION: " << myFC.getCurrentLocation().x << "," << myFC.getCurrentLocation().y <<
                "\tDrone Power: " << bW->getCurrentBattery() << " Watts" << endl;
        }
        
    }



    myFC.writeToPathHistoryDATFile();
    myFC.writeToPathHistoryTXTFile();
    vector<pair<LOCATION, double>> myPathHistory;
    myFC.writeToPathHistoryDATFile();
    myFC.readPathHistoryDATFile();

    cout << "The total time it took to get to final destination is " << calculateTotalTime(myPathHistory) << " seconds." << endl;
    cout << "HERE IS THE FLIGHT PATH HISTORY " << endl;
    viewPathHistory(myFC.getPathHistory());
	return 0;
}