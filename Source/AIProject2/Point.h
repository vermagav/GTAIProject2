#ifndef POINT_H
#define POINT_H

#include "_config.h"

/* Point class for each coordinate in our world's representation */
class Point
{
private:
	int xCoordinate;
	int yCoordinate;
	double difficulty; // 0.0 - 1.0
	PointType type;

public:
	// Constructors
	Point(void): xCoordinate(0), yCoordinate(0), difficulty(0.0), type(TYPE_EMPTY){}
	Point(int x, int y): xCoordinate(x), yCoordinate(y), difficulty(0.0), type(TYPE_EMPTY){}
	Point(int x, int y, double d, PointType p): xCoordinate(x), yCoordinate(y), difficulty(d), type(p){}

	// Get and set
	int X(void) { return xCoordinate; }
	int Y(void) { return yCoordinate; }
	void X(int x) { xCoordinate = x; }
	void Y(int y) { yCoordinate = y; }
	PointType getType() { return type; }
	void setType(PointType t) {	type = t; }
	double getDifficulty() { return difficulty; }
	void setDifficulty(double d)
	{
		// Clip d to within expected difficulty range
		if(d < 0.0) { d = 0.0; }
		if(d > 1.0) { d = 1.0; }

		// Set difficulty
		difficulty = d;
	}

};

#endif