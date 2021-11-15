#include "Coord.h"
#include "NavSensor.h"

#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char** argv) {

	NavSensor n = NavSensor(5);
	vector<Coord> path = n.getNavSensorPath();
	int pathSize = path.size();

	for (int i = 0; i < pathSize; i++) {


		//Check next position for a collision (Amanuel)
		//
		//amanuel returns true/false, use index of collision
		//bool movedrone = true;

		//if (movedrone) {
		if (i == 2) {
			//hovermode on
			path = n.updatePathCollisionFoundAt(i);
			pathSize = path.size();
			//ask user if go home or create new path
			//if yes update Path (go around collision)
			//if no, update path to go home
		} else {

		}

		//Check water (Danny)
		//
		//Danny returns something
		bool waterCapacity = true;

		if (waterCapacity) {
			//if water is enough -> continue
			//if not enough, update path to go home
		}

		cout << "Current Location: " << path.at(i).getX() << ", " << path.at(i).getY()
			<< " Current Nav Speed: " << n.getNavSensorSpeed(3/*getSpeedFromAmanuel*/) << endl;
		//Sleep(1000);


	}

	return 0;

}