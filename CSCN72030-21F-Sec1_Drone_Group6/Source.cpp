#include "Coord.h"
#include "NavSensor.h"
#include "FlightController.h"
#include "batteryWater.h"
#include <iostream>

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

			bool MoveDrone = true;

			if (MoveDrone) {
				battery->decreaseBattery(12); // should happen in flight
				
				if (i == 7) {
					//hovermode on
					//path = n.updatePathCollisionFoundAt(i);
					path = n.updatePathGoHome(i);
					pathSize = path.size();
					//ask user if go home or create new path
					//if yes update Path (go around collision)
					//if no, update path to go home

					//amanuel functions here

				} else {

				}

				//Check water (Danny)
				//
				//Danny returns something
			
				
				if (battery->getWaterStorage() <= 0 && OnTheWayHomeWater == false) {
					//if water is enough -> continue
					//if not enough, update path to go home
					battery->closeHatch();
					OnTheWayHomeWater = true;
					n.updatePathGoHome(i);
				} else if (battery->getCurrentBattery() < battery->batteryAlert && OnTheWayHomeBattery == false) {
					battery->closeHatch();
					OnTheWayHomeBattery = true;
					n.updatePathGoHome(i);
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
				Sleep(3000);
				system("cls");

				// <- DISPLAY
				


			}

		}
	}

	return 0;

}