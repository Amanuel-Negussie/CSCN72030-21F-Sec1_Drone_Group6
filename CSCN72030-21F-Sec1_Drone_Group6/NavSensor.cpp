#include "NavSensor.h"

NavSensor::NavSensor(int size) {
	this->gridSize = size;
}

vector<Coord> NavSensor::getNavSensorPath() {
	this->initPath();
	return this->path;
}

int NavSensor::getNavSensorSpeed(int speed) {
	int roundTo = 5;
	return ((speed + roundTo / 2) / roundTo) * roundTo;

}

void NavSensor::initPath() {

	//Fileio
	string currLine;
	int tempX = 0;
	int tempY = 0;

	string comma = ",";

	fstream fileStream;
	fileStream.open("Coords/inital.txt", ios::in);

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

	this->generateNewPath();

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
	}

	return this->path;

}
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