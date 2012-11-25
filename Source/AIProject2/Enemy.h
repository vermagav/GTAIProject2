#ifndef ENEMY_H
#define ENEMY_H

#include "_config.h"
#include "Point.h"

/* Class representing a single enemy in the game world */
class Enemy
{
private:
	int id;
	Point point;

public:
	// Main Constructor
	Enemy(int id, int x, int y)
	{
		this->id = id;
		point = Point(x, y, DIFF_TYPE_ENEMY, TYPE_ENEMY);
	}

	// Get and sets
	Point getPoint(void) { return point; }
	void setPoint(int x, int y) { point.X(x); point.Y(y); }
	int getID(void) { return id; }
	void setID(int id) { this->id = id; }
};

#endif