
/*
	
	
  
    vector<LOCATION> myWritingVector;
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
                "\tDrone Power: " << battery->getCurrentBattery() << " Watts" << endl;
            myFC.setCurrentLocation(loc);
        }
    }
    myFC.writeToPathHistoryDATFile();
    myFC.writeToPathHistoryTXTFile();
    myFC.writeToPathHistoryDATFile();
    myFC.readPathHistoryDATFile();
*/



#include "Coord.h"
#include "NavSensor.h"
#include "FlightController.h"
#include "batteryWater.h"
#include "Alert.h"
#include "Weather.h"
#include <iostream>
#include <iomanip>
#include "UserInterface.h"
#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

int main(int argc, char** argv) {
	batteryWater* battery = new batteryWater();
	NavSensor n = NavSensor();
	vector<Coord> path = n.getNavSensorPath();
	int pathSize = path.size();
	bool safetofly = true;
	Coord startingLocation(1, 1);
	FlightController myFC = FlightController(startingLocation, NORTH);
	bool OnTheWayHomeWater = false;
	bool OnTheWayHomeBattery = false;
	system("cls");
	if (safetofly) {
		battery->openHatch();

		for (int i = 0; i < pathSize; i++) {

			//Check next position for a collision (Amanuel)
			//
			//amanuel returns true/false, use index of collision

			//FlightController(n.getCurrentCoord(i), 0.0);
			
			
		
			Coord temp2;
			temp2 = n.getCurrentCoord(i);
			myFC.setCurrentLocation(temp2);

			if (i < pathSize - 1) {
				Coord temp;
				temp = n.getCurrentCoord(i + 1);
				myFC.setFutureLocation(temp);
			}
			
				
		
			if (!myFC.MoveDrone(battery)) {
				
				
				//Check water (Danny)
				//
				//Danny returns something
			
				
				if (battery->getWaterStorage() <= 0 && OnTheWayHomeWater == false) {
					//if water is enough -> continue
					//if not enough, update path to go home
					battery->closeHatch();
					OnTheWayHomeWater = true;
					path = n.updatePathGoHome(i);
					pathSize = path.size();
				} else if (battery->getCurrentBattery() < battery->batteryAlert && OnTheWayHomeBattery == false) {
					battery->closeHatch();
					OnTheWayHomeBattery = true;
					path= n.updatePathGoHome(i);
					pathSize = path.size();
				}

				if (i >=0 && n.checkIfHome(i) && OnTheWayHomeWater == true) { // may crash ------------------------------

					OnTheWayHomeWater = false;
					
					battery->fill(100);
					battery->openHatch();
				}

				if (i >=0 && n.checkIfHome(i) && OnTheWayHomeBattery == true) { // may crash ------------------------------
					OnTheWayHomeBattery = false;
					battery->startCharging();
					while (battery->getCurrentBattery() <= 100) {
						if (battery->getCurrentBattery() > 100) {
							battery->decreaseBattery(SCALER);
						}
						system("cls");
						battery->update();
						Sleep(100);
					}
					battery->openHatch();
				}
				// -> DISPLAY
				system("cls");
				battery->update();
				cout << "\nCurrent Location: " << path.at(i).getX() << ", " << path.at(i).getY()
					<< " Current Nav Speed: " << n.getNavSensorSpeed(3/*getSpeedFromAmanuel*/) << endl;
				Sleep(20);
				system("cls");

				// <- DISPLAY
				


			}
			else {
				
					//hovermode on
					path = n.updatePathCollisionFoundAt(i);
					//path = n.updatePathGoHome(i);
					pathSize = path.size();
					//ask user if go home or create new path
					//if yes update Path (go around collision)
					//if no, update path to go home

					//amanuel functions here
				

			}

		}
		

	}
	//viewPathHistory(myFC.getPathHistory());
	//cout << "Total Time : " << calculateTotalTime(myFC.getPathHistory());

    cout << "The total time it took to get to final destination is " <<fixed << setprecision(2) << calculateTotalTime(myFC.getPathHistory()) << " seconds." << endl;
    cout << "HERE IS THE FLIGHT PATH HISTORY " << endl;
    viewPathHistory(myFC.getPathHistory());
	return 0;

}