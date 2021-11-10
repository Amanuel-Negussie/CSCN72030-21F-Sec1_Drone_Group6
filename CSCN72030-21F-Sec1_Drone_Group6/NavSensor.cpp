#include "NavSensor.h"

NavSensor::NavSensor(int size) {

	this->gridSize = size;

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
}

vector<Coord> NavSensor::getNavSensorPath() {

	return this->path;

}

vector<Coord> NavSensor::updatePathCollisionFoundAt(int) {

	return this->path;

}

vector<Coord> NavSensor::updatePathGoHome() {

	return this->path;

}

vector<Coord> NavSensor::updatePathGoChargingStation() {

	return this->path;

}

vector<Coord> NavSensor::updatePathGoWaterStation() {

	return this->path;

}

int NavSensor::getNavSensorSpeed(int speed) {

	int roundTo = 5;
	return ((speed + roundTo / 2) / roundTo) * roundTo;

}
