
#include <iostream>
#include <iomanip>
#include "batteryWater.h"
#include "UserInterface.h"
#include "FlightController.h"
#include "NavSensor.h"


int main() {
	connection* connect = new connection((char*) "A1", (char*) "a2");
	Coord startingLocation(0, 0);
	FlightController myFC = FlightController(startingLocation, WEST);
    batteryWater* bW = new batteryWater();
    vector<LOCATION> myWritingVector;
    srand(time(0));
    for (int i = 0; i < 20; i++)
    {
        LOCATION thisVector;
        thisVector.setLocation(9, rand() % 10);
        myWritingVector.push_back(thisVector);
    }

    myFC.writeToCollisionDATFile(myWritingVector);
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

    myFC.setRequestedSpeed(GIVEN_SPEED);
    for (Coord& loc : coolPath)
    {
        myFC.setFutureLocation(loc);
        myFC.setRequestedSpeed(rand() % 10);
        if(!myFC.MoveDrone(bW))
        {       
            break;
        }
        else
        {
            cout << "LOCATION: " << myFC.getCurrentLocation().x << "," << myFC.getCurrentLocation().y <<
                "\tDrone Power: " << bW->getCurrentBattery() << " Watts" << endl;
            myFC.setCurrentLocation(loc);
        }
    }
    myFC.writeToPathHistoryDATFile();
    myFC.writeToPathHistoryTXTFile();
    myFC.writeToPathHistoryDATFile();
    myFC.readPathHistoryDATFile();

    cout << "The total time it took to get to final destination is " <<fixed << setprecision(2) << calculateTotalTime(myFC.getPathHistory()) << " seconds." << endl;
    cout << "HERE IS THE FLIGHT PATH HISTORY " << endl;
    viewPathHistory(myFC.getPathHistory());
	return 0;
}