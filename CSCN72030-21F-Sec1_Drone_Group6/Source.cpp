


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


#define FIELDS_DIR "./Fields//"
using namespace std;

int main(int argc, char** argv) {
	bool leave = false;
	int input = 0;
	int select = 0;
	while (leave == false) {
		system("cls");
		cout << "\t\t\t    WELCOME TO DRONE 1_Prototype INTERFACE";
		cout << "\n\t\t\t------------------------------------------";
		cout << "\n1. Add New Field\n";
		cout << "2. Delete Field\n";
		cout << "3. Water a Field\n";
		cout << "4. Shutdown\nEnter :";
		cin >> input;
		if (input > 4 && input < 0) {
			leave = false;
		}
		else {
			switch (input) {
			case 1:
				select = 1;
				leave = true;
				break;
			case 2:
				select = 2;
				leave = true;
				break;
			case 3:
				select = 3;
				leave = true;
				break;
			case 4:
				exit(2);
				break;
			default:
				leave = false; // shouldnt be hit but just in case
				break;
			}
		}
	
	if (leave == true && select == 1) { // add new field
		string name;
		int size;
		system("cls");
		cout << "\t\t\t Add a Field\n\t\t\t-------------------\n";
		cout << "Enter the field ID/Name :";
		cin >> name;
		cout << "\n 1. 5x5 Grid\n 2. 10x10Grid\n";
		cout << "Please enter a field Size [1,2] :";
		cin >> size;



		// Create and open a text file
		name = "./Fields//" + name;
		ofstream MyFile(name);

		// Write to the file
		MyFile << size;
		// Close the file
		MyFile.close();

		// write data to file | add ND to file for no date, date should be added after it is watered
		leave = false; // go back to menu after field is watered
	}
	if (leave == true && select == 2) { // delete field
		string name = "sds";

		
		
		char command[50] = "dir Fields\  /b";
		system("cls");
		cout << "\t\t\t   Remove a Field\n\t\t\t-------------------\n";
		
		system(command);
		cout << "\nEnter the field Name : ";
		cin >> name;
		name = "./fields//" + name;
		remove(name.c_str());
		leave = false; // go back to menu after field is watered
	}
	if (leave == true && select == 3) { // select a field to water

		string name = "sds";
		char command[50] = "dir Fields\  /b";
		system("cls");
		cout << "\t\t\t   Water a Field\n\t\t\t-------------------\n";

		system(command);
		cout << "\nEnter the field Name : ";
		cin >> name;
		name = "./fields//" + name;
		fstream file;
		file.open(name, ios::in);
		if (file.is_open()) {
			select = 4;
		}
		else {
			cout << "\n Incorrect Name.... <Enter> to continue";
			cin >> name;
			leave = false; // go back to menu after field is watered
		}
	}






	 // water a field
	if (leave == true && select == 4) { // if can exit menu and a field has been selected
		leave = false; // go back to menu after field is watered
		batteryWater* battery = new batteryWater();
		Coord startingLocation(1, 1);
		FlightController myFC = FlightController(startingLocation, NORTH);
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



				Coord temp2;
				temp2 = n.getCurrentCoord(i);
				myFC.setCurrentLocation(temp2);

				if (i < pathSize - 1) {
					Coord temp;
					temp = n.getCurrentCoord(i + 1);
					myFC.setFutureLocation(temp);
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
					}
					else if (battery->getCurrentBattery() < battery->batteryAlert && OnTheWayHomeBattery == false) {
						battery->closeHatch();
						OnTheWayHomeBattery = true;
						path = n.updatePathGoHome(i);
						pathSize = path.size();
					}

					if (i >= 0 && n.checkIfHome(i) && OnTheWayHomeWater == true) { // may crash ------------------------------

						OnTheWayHomeWater = false;

						battery->fill(100);
						battery->openHatch();
					}

					if (i >= 0 && n.checkIfHome(i) && OnTheWayHomeBattery == true) { // may crash ------------------------------
						OnTheWayHomeBattery = false;
						battery->startCharging();
						while (battery->getCurrentBattery() <= 100) {
							if (battery->getCurrentBattery() > 100) {
								battery->decreaseBattery(SCALER);
							}
							system("cls");
							battery->update();
							Sleep(150);
							
						}
						battery->openHatch();
					}
					// -> DISPLAY
					system("cls");
					battery->update();
					cout << "\nCurrent Location: " << path.at(i).getX() << ", " << path.at(i).getY()
						<< " Current Nav Speed: " << n.getNavSensorSpeed(3/*getSpeedFromAmanuel*/) << endl;
					Sleep(500);
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

		cout << "The total time it took to get to final destination is " << fixed << setprecision(2) << calculateTotalTime(myFC.getPathHistory()) << " seconds." << endl;
		cout << "HERE IS THE FLIGHT PATH HISTORY " << endl;
		viewPathHistory(myFC.getPathHistory());
		return 0;
	} // if temp
	} // while leave == false
}