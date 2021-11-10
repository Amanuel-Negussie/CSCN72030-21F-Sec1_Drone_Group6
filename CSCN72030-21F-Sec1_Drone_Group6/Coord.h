#pragma once
using namespace std;

class Coord {
protected:
	int XCoord;
	int YCoord;

public:
	Coord();
	Coord(int, int);
	int getX();
	int getY();
	void setCoord(int, int);

private:

};