#include "Coord.h"
#include "NavSensor.h"
#include "FlightController.h"
//#include "batteryWater.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char** argv) {

	NavSensor n = NavSensor();
	vector<Coord> path = n.getNavSensorPath();
	int pathSize = path.size();

	for (int i = 0; i < pathSize; i++) {


		//Check next position for a collision (Amanuel)
		//
		//amanuel returns true/false, use index of collision

		//FlightController(n.getCurrentCoord(i), 0.0);
		bool MoveDrone = true;
		if (MoveDrone) {
			if (i == 200) {
				//hovermode on
				path = n.updatePathCollisionFoundAt(i);
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
			bool waterCapacity = false; // false for now
			int battery = 100;
			bool OnTheWayHomeWater = false;
			bool OnTheWayHomeBattery = false;

			if (waterCapacity) {
				//if water is enough -> continue
				//if not enough, update path to go home
				OnTheWayHomeWater = true;
				n.updatePathGoHome(i);
			} else if (battery < 50) {
				OnTheWayHomeBattery = true;
				n.updatePathGoHome(i);
			}

			if (n.checkIfHome(i) && OnTheWayHomeWater == true) {
				OnTheWayHomeWater = false;
			}

			if (n.checkIfHome(i) && OnTheWayHomeBattery == true) {
				OnTheWayHomeBattery = false;
			}

			cout << "Current Location: " << path.at(i).getX() << ", " << path.at(i).getY()
				<< " Current Nav Speed: " << n.getNavSensorSpeed(3/*getSpeedFromAmanuel*/) << endl;
			//Sleep(1000);


		}

	}

	return 0;

}