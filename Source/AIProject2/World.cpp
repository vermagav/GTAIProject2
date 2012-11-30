#include "World.h"
#include <time.h>
#include <conio.h>
#include <iostream>
//#include <stdlib.h>

using std::vector;
using std::cout;

/* Initializes and populates the game world */
void World::initWorld()
{
	// ----------------------
	// Initialize Enemies
	// ----------------------
	// Initialize variables for readability later
	int x = 0, y = 0;
	int maxX = LEVEL_MAX_X - ENEMY_GENERATION_BUFFER;
	int minX = LEVEL_MIN_X + ENEMY_GENERATION_BUFFER;
	int maxY = LEVEL_MAX_Y - ENEMY_GENERATION_BUFFER;
	int minY = LEVEL_MIN_Y + ENEMY_GENERATION_BUFFER;
	
	srand(time(0));

	for(vector<Enemy>::size_type i = 0; i != NUM_ENEMIES; i++)
	{
		// Generate random numbers for x, y
		x = rand() % (maxX - minX) + minX;
		y = rand() % (maxY - minY) + minY;

		// TODO: Make sure x, y are within walls and not on top of another enemy

		// Add this new enemy to the main vector
		enemies.push_back(Enemy(i, x, y));
	}

	// ----------------------
	// Populate Level
	// ----------------------
	int pointCount = 0;
	vector<vector<Point>> levelVector;
	vector<Point> levelRow;

	// Create empty level first
	for(int y = LEVEL_MIN_Y; y <= LEVEL_MAX_Y; y++)
	{
		for(int x = LEVEL_MIN_X; x<= LEVEL_MAX_X; x++)
		{
			// Populate row for given y coordinate
			levelRow.push_back(Point(x, y, DIFF_TYPE_EMPTY, TYPE_EMPTY));
			pointCount++;
		}
		// Add row to 2D levelVector
		levelVector.push_back(levelRow);
	}

	// Copy our now populated level vector to the main Level object
	level.setLevel(levelVector);

	// Add enemies
	for(vector<Enemy>::size_type i = 0; i != enemies.size(); i++)
	{
		// get enemy x and y
		x = enemies[i].getPoint().X();
		y = enemies[i].getPoint().Y();

		// Change existing point in level object to enemy
		level.setTypeToEnemy(x, y);
			// Alt method: level.modifyPoint(x, y, enemies[i].getPoint());

		// set surrounding points to approaching enemy
		for(int yArg = y-1; yArg <= y+1; yArg++)
		{
			for(int xArg = x-1; xArg <= x+1; xArg++)
			{
				if(xArg <= LEVEL_MAX_X && xArg >= LEVEL_MIN_X && yArg <= LEVEL_MAX_Y && yArg >= LEVEL_MIN_Y)
				{
					// set to everything except the enemy point itself
					if(!(xArg == x && yArg == y))
					{
						level.setTypeToApproachEnemy(xArg, yArg);
					}
				}
			}
		}
	}

	// Add goal node
	level.setTypeToGoal(LEVEL_MAX_X, LEVEL_MAX_Y);

	// TODO: Add rooms
	//		-- Add walls (TYPE_OBSTACLE)
	//		-- Add door (TYPE_DOOR)
}

/* Function for drawing the contents of the world */
void World::drawWorld()
{
	// Clear the screen
	//system("CLS");

	// Go through Level and write to console
	for(int y = LEVEL_MIN_Y; y <= LEVEL_MAX_Y; y++)
	{
		for(int x = LEVEL_MIN_X; x <= LEVEL_MAX_X; x++)
		{
			if(level.getPoint(x, y).getType() == TYPE_EMPTY)
				cout<<".";
			if(level.getPoint(x, y).getType() == TYPE_ENEMY)
				cout<<"X";
			if(level.getPoint(x, y).getType() == TYPE_APPROACH_ENEMY)
				cout<<"~";
			if(level.getPoint(x, y).getType() == TYPE_GOAL)
				cout<<"G";
		}
		cout<<"\n";
	}
}
