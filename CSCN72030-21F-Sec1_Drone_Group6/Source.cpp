
#include <iostream>
#include <iomanip>


#include "Coord.h"
#include "NavSensor.h"
#include "FlightController.h"
#include "batteryWater.h"
#include "Alert.h"
#include "Weather.h"
#include "UserInterface.h"

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

vector<LOCATION> inline collisionCreator(int upperLimit)
{
	vector<LOCATION> col; 
	LOCATION l; 
	for (int i = 0; i < 5; i++)
	{
		int x = (rand() % upperLimit + 1);
		int y = (rand() % upperLimit + 1);
		l.setLocation(x, y);
		col.push_back(l);
	}
	return col;
}

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
	vector<LOCATION> col = collisionCreator(5); //this returns 5 random coordinates just so i can test the writing of collisions to file 
	string collisionFileName("Collision2.dat");
	if (writeCollisionToDATFile(col, collisionFileName))
		cout << "SUCCESS" << endl;
	else
		cout << "FAILURE" << endl;
	string collisionFileName2("Collision2.txt");
	if (writeCollisionToTXTFile(col, collisionFileName2))
		cout << "SUCCESS in sending TXT";
	else
		cout << "FAILURE in sending TXT" << endl;
	
	if (!myFC.readCollisionDATFile(collisionFileName)) //this reads collision data file into Flight Controller module
		std::cout << "This does not work for reading in file to Flight Controller" << endl;

	viewCollisions(myFC.getCollisionList()); //

	system("cls");
	if (safetofly) {
		battery->openHatch();

		for (int i = 0; i < pathSize; i++) {

			//Check next position for a collision (Amanuel)
			//
			//amanuel returns true/false, use index of collision

			//FlightController(n.getCurrentCoord(i), 0.0);
			
			
		
			/*Coord temp2;
			temp2 = n.getCurrentCoord(i);*/
			myFC.setCurrentLocation(n.getCurrentCoord(i)); //Amanuel fixing issue #14

			if (i < pathSize - 1) {
				/*Coord temp;
				temp = n.getCurrentCoord(i + 1);*/
				myFC.setFutureLocation(n.getCurrentCoord(i+1)); //Amanuel fixing issue #14
			}
			
				
			if (myFC.MoveDrone(battery)) {
				
				
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
	writePathHistoryToTXTFile(myFC.getPathHistory(), "PathHistory.txt");

	return 0;

}



