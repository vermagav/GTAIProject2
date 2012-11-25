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
	// Each entity in level is of the Point class
	vector<Point> levelVector;

public:
	// Get access to level
	vector<Point> getLevel() { return levelVector; }

	// Fetch point by x and y
	Point getPoint(int x, int y)
	{
		// Method 1: Search
		for(vector<Point>::size_type i = 0; i != levelVector.size(); i++)
		{
			if(levelVector[i].X() == x && levelVector[i].Y() == y)
				return levelVector[i];
		}
		
		// Method 2: Use min/max to fetch index directly (faster)
		/*int returnIndex = (y * LEVEL_MAX_X) + x + 1;
		return levelVector[returnIndex];*/
	}
	
	// Add point to the level
	void addPoint(Point p)
	{
		levelVector.push_back(p);
	}

	// Modify existing point in the level
	void modifyPoint(int x, int y, Point p)
	{
		// Search and set
		for(vector<Point>::size_type i = 0; i != levelVector.size(); i++)
		{
			if(levelVector[i].X() == x && levelVector[i].Y() == y)
				levelVector[i] = p;
		}	
	}
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