
#include <iostream>
#include <iomanip>


#include "Coord.h"
#include "NavSensor.h"
#include "FlightController.h"
#include "batteryWater.h"
#include "Alert.h"
#include "Weather.h"
#include "UserInterface.h"
#include "Lidar.h"
#ifdef _WIN32
#include <Windows.h>
#endif


#define FIELDS_DIR "./Fields//"
using namespace std;


int main(int argc, char** argv) {


	Weather w("Sunny");
	bool leave = false;
	int input = 0;
	int select = 0;
	NavSensor n;
	while (leave == false) {
		system("cls");
		cout << "\t\t\t    WELCOME TO DRONE 1_Prototype INTERFACE";
		cout << "\n\t\t\t------------------------------------------";
		cout << "\n1. Add New Field\n";
		cout << "2. Delete Field\n";
		cout << "3. Water a Field\n";
		cout << "4. Choose Weather\n";
		cout << "5. Shutdown\nEnter :";
		cin >> input;
		string str;
		if (input > 5 && input < 0) {
			leave = false;
		} else {
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
				w = Weather("Sunny");

				cout << "Please enter the weather or type 'Custom' to create one: ";
				cin >> str;
				cout << endl;
				if (str != "Custom") {
					w = Weather(str);
				} else {
					w.createCustomWeather();
				}

				break;
			case 5:
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
			cout << "\n 1. 5x5 Grid\n 2. 10x10 Grid (Experimental ~ Not Working)\n";
			cout << "Please enter a field Size [1,2] :";
			cin >> size;

			if (size == 2) {
				size = 10;
			} else {
				size = 5;
			}


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
				string gridSelectionFromFile;
				getline(file, gridSelectionFromFile);
				int gridSelection = stoi(gridSelectionFromFile);
				n = NavSensor(gridSelection);
				select = 4;
			} else {
				cout << "\n Incorrect Name.... <Enter> to continue";
				cin >> name;
				leave = false; // go back to menu after field is watered
			}
		}






		// water a field
		if (leave == true && select == 4) { // if can exit menu and a field has been selected

			leave = false; // go back to menu after field is watered
			batteryWater* battery = new batteryWater();
			//battery->fill(100);
			//battery->swapBattery();
			Coord startingLocation(1, 1);
			FlightController myFC = FlightController(startingLocation, NORTH);
			
			myFC.readCollisionDATFile(COLLISIONS_DAT_FILENAME);


			vector<Coord> path = n.getNavSensorPath();
			int pathSize = path.size();

			bool OnTheWayHomeWater = false;
			bool OnTheWayHomeBattery = false;
			system("cls");
			setCursorPosition(0, 0);
			cout << "                                                                                                                                                 ";
			battery->initScreen();
			if (w.safeToFly) {
				battery->openHatch();

				for (int i = 0; i < pathSize; i++) {

					//Check next position for a collision (Amanuel)
					//batteryWater* battery = new batteryWater();
					//NavSensor n = NavSensor();
					//vector<Coord> path = n.getNavSensorPath();
					//int pathSize = path.size();
					//bool safetofly = true;
					//battery->initScreen();
					//bool OnTheWayHomeWater = false;
					//bool OnTheWayHomeBattery = false;


					//if (safetofly) {
						//battery->openHatch();

					//for (int i = 0; i < pathSize; i++) {

						//Check next position for a collision (Amanuel)
						//
						//amanuel returns true/false, use index of collision

						//FlightController(n.getCurrentCoord(i), 0.0);


					/*Coord temp;
					temp = n.getCurrentCoord(i);
					myFC.setCurrentLocation(temp);

					if (i < pathSize - 1) {
						Coord temp2;
						temp2 = n.getCurrentCoord(i + 1);
						
					}*/

					myFC.setCurrentLocation(n.getCurrentCoord(i));

					if (i < pathSize - 1) {
						myFC.setFutureLocation(n.getCurrentCoord(i + 1));
					} else {
						myFC.setFutureLocation(n.getCurrentCoord(i));
					}
					
					

					if (myFC.MoveDrone(battery)) {


						//Check water (Danny)
						//
						//Danny returns something

						// -> DISPLAY


						setCursorPosition(0, 1);
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 15);
						// OUTPUT WINDOW
						battery->update(); // TOP BAR
						setCursorPosition(0, 3);
						w.displayWeather();
						setCursorPosition(0, 5);
						cout << "                                                                                         " << endl;;
						cout << "Current Location: " << path.at(i).getX() << ", " << path.at(i).getY()
							<< " Current Nav Speed: " << n.getNavSensorSpeed(myFC.getSpeed()) <<
							"\tCurrent Drone Direction: " << myFC.getPathHistory().back().direction << " " << endl;
						setCursorPosition(0, 8);
						cout << outputLidarData(myFC.getLidarData()) << endl;
						// -> PUT COUT'S HERE FOR NEXT
						setCursorPosition(0, 15);
						cout << "                                                   \n                                                                   ";

						// cout w.weather
						Sleep(1000);


						// <- DISPLAY

						if (battery->getCurrentBattery() < battery->batteryAlert && OnTheWayHomeBattery == false || battery->getWaterStorage() <= 0 && OnTheWayHomeWater == false) {
							battery->closeHatch();
							OnTheWayHomeBattery = true;
							OnTheWayHomeWater = true;
							path = n.updatePathGoHome(i);
							pathSize = path.size();
						}

						if (n.checkIfHome(i) && OnTheWayHomeBattery == true) { // may crash ------------------------------
							OnTheWayHomeBattery = false;
							battery->startCharging();
							while (battery->getCurrentBattery() < 100) {


								battery->update();
								Sleep(100);

							}
							battery->endCharging();
							battery->update();
							battery->openHatch();
						}
						if (n.checkIfHome(i) && OnTheWayHomeWater == true) { // may crash ------------------------------

							OnTheWayHomeWater = false;
							battery->fill(100);
							battery->openHatch();
						}



					} else {


						setCursorPosition(0, 1);
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 15);
						// OUTPUT WINDOW
						battery->update(); // TOP BAR
						setCursorPosition(0, 3);
						w.displayWeather();
						setCursorPosition(0, 5);
						cout << "                                                                                         " << endl;;
						cout << "Current Location: " << path.at(i).getX() << ", " << path.at(i).getY()
							<< " Current Nav Speed: " << n.getNavSensorSpeed(myFC.getSpeed()) <<
							"\tCurrent Drone Direction: " << myFC.getPathHistory().back().direction << " " << endl;
						setCursorPosition(0, 8);
						cout << outputLidarData(myFC.getLidarData()) << endl;
						// -> PUT COUT'S HERE FOR NEXT
						setCursorPosition(0, 15);
						cout << "                                                   \n                                                                   ";

						// cout w.weather
						Sleep(1000);



						//hovermode on
						path = n.updatePathCollisionFoundAt(i);
						//path = n.updatePathGoHome(i);
						pathSize = path.size();
						//ask user if go home or create new path
						//if yes update Path (go around collision)
						//if no, update path to go home

						//amanuel functions here


					}

					//} // considered taking this out because double use of MoveDrone wasn't helping with rendering -Amanuel Negussie


				}
				//viewPathHistory(myFC.getPathHistory());
				//cout << "Total Time : " << calculateTotalTime(myFC.getPathHistory());
				system("cls");


				cout << "The total time it took to get to final destination is " << fixed << setprecision(2) << calculateTotalTime(myFC.getPathHistory()) << " seconds." << endl;
				cout << "--------------------------------" << endl;
				viewPathHistory(myFC.getPathHistory());
		
				writePathHistoryToTXTFile(myFC.getPathHistory(), PATH_HISTORY_TXT_FILENAME);


				system("pause");
				//} // if temp

			}// while leave == false
			else {
				system("cls");
				cout << "UNSAFE TO FLY\n";
				system("pause");
			}
		}

	}

	return 0;
}

