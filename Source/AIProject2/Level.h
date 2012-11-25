#ifndef LEVEL_H
#define LEVEL_H

#include "_config.h"
#include "Point.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cerr;

/* This class represents the top-level Level of the game world */
class Level
{
private:
	// Outer vector = Y, Inner vector = X
	vector<vector<Point>> levelVector;

public:
	// Add populated level
	void setLevel(vector<vector<Point>> level) { levelVector = level; }
	// Get access to full level
	vector<vector<Point>> getLevel() { return levelVector; }
	// Fetch point by x and y
	Point getPoint(int x, int y) { return levelVector[y][x]; }
	// Modify existing point in the level
	void modifyPoint(int x, int y, Point point) { levelVector[y][x] = point; }
};

#endif

/*
 * Visual representation of Level by x and y coordinates:
 *
 *	.....x--->..........
 *	....................
 *	...y................
 *	...|................
 *	...|................
 *	---V................
 *	....................
 */