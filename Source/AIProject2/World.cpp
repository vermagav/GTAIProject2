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
	int x = 0, y = 0;
	srand(time(0));

	for(vector<Enemy>::size_type i = 0; i != NUM_ENEMIES; i++)
	{
		// Generate random numbers for x, y
		x = ENEMY_GENERATION_BUFFER + rand() % (LEVEL_MAX_X - ENEMY_GENERATION_BUFFER);
		y = ENEMY_GENERATION_BUFFER + rand() % (LEVEL_MAX_Y - ENEMY_GENERATION_BUFFER);

		// TODO: Make sure x, y are within walls and not on top of another enemy

		// Add this new enemy to the main vector
		enemies.push_back(Enemy(i, x, y));
	}

	// ----------------------
	// Populate Level
	// ----------------------
	int pointCount = 0;

	// Create empty level first
	for(int y = LEVEL_MIN_Y; y <= LEVEL_MAX_Y; y++)
	{
		for(int x = LEVEL_MIN_X; x<= LEVEL_MAX_X; x++)
		{
			level.addPoint(Point(x, y, DIFF_TYPE_EMPTY, TYPE_EMPTY));
			pointCount++;
		}
	}

	//Add enemies
	Point enemyPoint;
	Point enemyApproachPoint;
	for(vector<Enemy>::size_type i = 0; i != enemies.size(); i++)
	{
		// get enemy x and y
		x = enemies[i].getPoint().X();
		y = enemies[i].getPoint().Y();

		// go to levelVector point of x and y
		for(int j = 0; j < pointCount; j++)
		{
			// set point to enemy
			if(level.getPoint(x, y).X() == x && level.getPoint(x, y).Y() == y)
			{
				enemyPoint = Point(x, y, DIFF_TYPE_ENEMY, TYPE_ENEMY);
				level.modifyPoint(x, y, enemyPoint);
			}
			
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
							enemyApproachPoint = Point(x, y, DIFF_TYPE_APPROACH_ENEMY, TYPE_APPROACH_ENEMY);
							level.modifyPoint(xArg, yArg, enemyApproachPoint);
						}
					}
				}
			}
		}
	}

	// TODO: Add rooms
	//		-- Add walls
	//		-- Add door
}

/* Function for drawing the contents of the world */
void World::drawWorld()
{
	// Clear the screen
	system("CLS");

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
		}
		cout<<"\n";
	}
}

