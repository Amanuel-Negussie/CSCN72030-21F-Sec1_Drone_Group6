#include "NavSensor.h"

NavSensor::NavSensor() {

	this->selection = this->userPathSelection();

	switch (this->selection) {
	case 1:
		this->gridSize = 5;
		break;
	case 2:
		this->gridSize = 10;
		break;
	default:
		this->gridSize = 5;
		break;
	}
}

int NavSensor::userPathSelection() {

	cout << "Please select a start path (1 or 2):" << endl
		<< "1. 5x5 Grid" << endl
		<< "2. 10x10 Grid" << endl
		<< ": ";
	
	int selection = 1;

	try {
		
		cin >> selection;

	} catch(exception e) {

		//alert invalid path selection, using path 1
		//Alert a = Alert(300); // 300 - Invalid path entry
		selection = 1;

	}

	if (selection > 2 || selection < 1) {
		//alert invalid path selection, using path 1
		//Alert a = Alert(300); // 300 - Invalid path entry
		selection = 1;
	}

	return selection;

}

vector<Coord> NavSensor::getNavSensorPath() {
	this->initPath();
	return this->path;
}

int NavSensor::getNavSensorSpeed(int speed) {
	int roundTo = 5;
	return ((speed + roundTo / 2) / roundTo) * roundTo;

}

Coord NavSensor::getCurrentCoord(int index) {
	return this->path.at(index);
}

void NavSensor::initPath() {

	//Fileio
	string currLine;
	int tempX = 0;
	int tempY = 0;

	string comma = ",";
	fstream fileStream;

	switch (this->selection) {
	case 1:
		fileStream.open("Coords/initalOne.txt", ios::in);
		break;
	case 2:
		fileStream.open("Coords/initalTwo.txt", ios::in);
		break;
	default:
		fileStream.open("Coords/initalOne.txt", ios::in);
		break;
	}

	while (fileStream.is_open()) {

		if (!getline(fileStream, currLine)) {
			return;

		} else {
			tempX = stoi(currLine.substr(0, currLine.find(comma)));
			tempY = stoi(currLine.substr(currLine.find(comma) + 1, currLine.length() - 1));
			Coord cTemp(tempX, tempY);
			this->path.push_back(cTemp);

		}

	}

}

vector<Coord> NavSensor::updatePathCollisionFoundAt(int index) {

	//this->generateNewPath();

	Coord cCoord = this->path.at(index);

	if (index > 0 && index < (this->gridSize * this->gridSize) - 1) {
		Coord cCoordPrev = this->path.at(index - 1);
		Coord cCoordAfter = this->path.at(index + 1);

		if ((cCoord.getY() - cCoordAfter.getY()) == 0) {

			//trace backwards 1 step
			Coord cCoordPrevPrev = this->path.at(index - 1);
			this->path.at(index + 1) = cCoordPrevPrev;

			//going up
		} else if ((cCoord.getY() - cCoordAfter.getY()) < 0) {

			if (cCoordAfter.getY() == this->gridSize || cCoordAfter.getY() == 1) {

				this->path.at(index + 1).setCoord(cCoord.getX() + 1, cCoord.getY());

			} else if (cCoordAfter.getX() == this->gridSize) {

				this->path.at(index + 1).setCoord(cCoord.getX() - 1, cCoord.getY());
				//add 2 coordinates to go around
				Coord newCoordOne(cCoord.getX() - 1, cCoord.getY() + 1);
				this->path.insert(this->path.begin() + index + 2, newCoordOne);
				Coord newCoordTwo(cCoord.getX() - 1, cCoord.getY() + 2);
				this->path.insert(this->path.begin() + index + 3, newCoordTwo);

			} else {

				//change collision coordinate on path
				this->path.at(index + 1).setCoord(cCoord.getX() + 1, cCoord.getY());
				//add 2 coordinates to go around
				Coord newCoordOne(cCoord.getX() + 1, cCoord.getY() + 1);
				this->path.insert(this->path.begin() + index + 2, newCoordOne);
				Coord newCoordTwo(cCoord.getX() + 1, cCoord.getY() + 2);
				this->path.insert(this->path.begin() + index + 3, newCoordTwo);
			}

		} else {
			//going down
			if (cCoordAfter.getY() == this->gridSize || cCoordAfter.getY() == 1) {

				this->path.at(index + 1).setCoord(cCoord.getX() + 1, cCoord.getY());

			} else if (cCoordAfter.getX() == this->gridSize) {

				//change collision coordinate on path
				this->path.at(index + 1).setCoord(cCoord.getX() - 1, cCoord.getY());
				//add 2 coordinates to go around
				Coord newCoordOne(cCoord.getX() - 1, cCoord.getY() - 1);
				this->path.insert(this->path.begin() + index + 2, newCoordOne);
				Coord newCoordTwo(cCoord.getX() - 1, cCoord.getY() - 2);
				this->path.insert(this->path.begin() + index + 3, newCoordTwo);

			} else {

				//change collision coordinate on path
				this->path.at(index + 1).setCoord(cCoord.getX() - 1, cCoord.getY());
				//add 2 coordinates to go around
				Coord newCoordOne(cCoord.getX() - 1, cCoord.getY() - 1);
				this->path.insert(this->path.begin() + index + 2, newCoordOne);
				Coord newCoordTwo(cCoord.getX() - 1, cCoord.getY() - 2);
				this->path.insert(this->path.begin() + index + 3, newCoordTwo);
			}

		}

	} else {
		//(alert)
		//Alert a = Alert(301); // 301 - Collision not found // should never happen
	}

	return this->path;

}

vector<Coord> NavSensor::updatePathGoHome(int index) {

	Coord cCoord = this->path.at(index);

	if (index > 0) {

		//left side
		if (cCoord.getY() > 0 && cCoord.getX() == 1) {
			//insert into vector until home
			int counter = 1;
			for (int i = cCoord.getY(); i > 1; i--) {
				Coord newCoord(cCoord.getX(), cCoord.getY() - counter);
				this->path.insert(this->path.begin() + index + counter, newCoord);
				counter++;
			}

			//add in reverse to get back to position
			for (int i = 2; i <= cCoord.getY(); i++) {
				Coord newCoord(cCoord.getX(), i);
				this->path.insert(this->path.begin() + index + counter, newCoord);
				counter++;
			}

			//right
		} else if (cCoord.getY() == 1 && cCoord.getX() > 1) {

			int counter = 1;
			for (int i = cCoord.getX(); i > 1; i--) {
				Coord newCoord(cCoord.getX() - counter, cCoord.getY());
				this->path.insert(this->path.begin() + index + counter, newCoord);
				counter++;
			}

			for (int i = 2; i <= cCoord.getX(); i++) {
				Coord newCoord(i, cCoord.getY());
				this->path.insert(this->path.begin() + index + counter, newCoord);
				counter++;
			}


			//middle
		} else {

			int counter = 1;
			for (int i = cCoord.getX(); i > 1; i--) {
				Coord newCoord(cCoord.getX() - counter, cCoord.getY());
				this->path.insert(this->path.begin() + index + counter, newCoord);
				counter++;
			}

			int counterY = 1;
			for (int i = cCoord.getY(); i > 1; i--) {
				Coord newCoord(1, cCoord.getY() - counterY);
				this->path.insert(this->path.begin() + index + counter, newCoord);
				counter++;
				counterY++;
			}

			for (int i = 2; i <= cCoord.getY(); i++) {
				Coord newCoord(1, i);
				this->path.insert(this->path.begin() + index + counter, newCoord);
				counter++;
			}

			for (int i = 2; i <= cCoord.getX(); i++) {
				Coord newCoord(i, cCoord.getY());
				this->path.insert(this->path.begin() + index + counter, newCoord);
				counter++;
			}

		}

	} else {
		//already home
		//Alert a = Alert(302); // 302 - Unable to go home (Already Home)
	}

	return this->path;

}

bool NavSensor::checkIfHome(int index) {

	Coord cCoord = this->path.at(index);

	if (cCoord.getX() == home.getX() &&
		cCoord.getY() == home.getY()) {

		return true;

	} else {
		return false;
	}

}

/*
//temp usage for now
void NavSensor::generateNewPath() {

	vector<Coord> c;
	for (int i = 0; i < this->gridSize; i++) {
		if (i % 2 == 0) {
			for (int j = 0; j < this->gridSize; j++) {
				Coord temp(i + 1, j + 1);
				c.push_back(temp);
			}
		} else {
			for (int j = this->gridSize; j > 0; j--) {
				Coord temp(i + 1, j);
				c.push_back(temp);
			}
		}
	}
	this->path = c;
	//this->path.erase(next(this->path.begin(), index + 1), next(this->path.begin(), this->path.size()));
}
*/