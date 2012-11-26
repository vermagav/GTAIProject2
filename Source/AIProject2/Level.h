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

	// Fast type modification of a given point
	void setTypeToEnemy(int x, int y) { levelVector[y][x].setDifficulty(DIFF_TYPE_ENEMY); levelVector[y][x].setType(TYPE_ENEMY); }
	void setTypeToApproachEnemy(int x, int y) { levelVector[y][x].setDifficulty(DIFF_TYPE_APPROACH_ENEMY); levelVector[y][x].setType(TYPE_APPROACH_ENEMY); }
	void setTypeToObstacle(int x, int y) { levelVector[y][x].setDifficulty(DIFF_TYPE_OBSTACLE); levelVector[y][x].setType(TYPE_OBSTACLE); }
	void setTypeToDoor(int x, int y) { levelVector[y][x].setDifficulty(DIFF_TYPE_DOOR); levelVector[y][x].setType(TYPE_DOOR); }
	void setTypeToGoal(int x, int y) { levelVector[y][x].setDifficulty(DIFF_TYPE_GOAL); levelVector[y][x].setType(TYPE_GOAL); }
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