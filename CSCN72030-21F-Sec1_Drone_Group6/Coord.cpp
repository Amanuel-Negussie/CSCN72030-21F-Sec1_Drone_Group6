#include "Coord.h"

Coord::Coord() {
	XCoord = 0;
	YCoord = 0;
}

Coord::Coord(int x, int y) {
	XCoord = x;
	YCoord = y;
}

int Coord::getX() {
	return this->XCoord;
}

int Coord::getY() {
	return this->YCoord;
}

void Coord::setCoord(int x, int y) {
	this->XCoord = x;
	this->YCoord = y;
}