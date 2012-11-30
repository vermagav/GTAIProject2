/*
 * Configuration Settings for the Project
 * Ideally, these should be imported from a .ini file
 */
#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <iostream>

// Level Representation: Point Entity Types
enum PointType
{
	TYPE_EMPTY,
	TYPE_DOOR,
	TYPE_OBSTACLE,
	TYPE_APPROACH_ENEMY,
	TYPE_ENEMY,
	TYPE_GOAL
};

// Level Representation: Point Difficulties
const double DIFF_TYPE_EMPTY = 0.0;
const double DIFF_TYPE_DOOR = 0.0;
const double DIFF_TYPE_OBSTACLE = 0.4;
const double DIFF_TYPE_APPROACH_ENEMY = 0.8;
const double DIFF_TYPE_ENEMY = 1.0;
const double DIFF_TYPE_GOAL = 0.0;

// Level Representation: Enemy Population Buffer (from border of level)
const int ENEMY_GENERATION_BUFFER = 6;

// World's Game State
enum GameState
{
	GAMESTATE_RUNNING,
	GAMESTATE_FAIL,
	GAMESTATE_WIN,
	GAMESTATE_COUNT
};

// Start position of home agent
const int STARTX_HOMEAGENT = 0;
const int STARTY_HOMEAGENT = 0;
const int STARTX_GOAL = 31;
const int STARTY_GOAL = 31;

// Boundary constants for the level
const int LEVEL_MIN_X = 0;
const int LEVEL_MAX_X = 31;
const int LEVEL_MIN_Y = 0;
const int LEVEL_MAX_Y = 31;

// Maximum number of rows (depends on Y) and columns (depends on X)
const int LEVEL_NUM_ROWS = (LEVEL_MAX_Y - LEVEL_MIN_Y) + 1;
const int LEVEL_NUM_COLUMNS = (LEVEL_MAX_X - LEVEL_MIN_X) + 1;

// Number of enemies
const int NUM_ENEMIES = 5;

/* Algorithm Related Config */

	// Number of Functions ot be maximized in parallel
	const int NO_OBJECTIVE_FUNCTIONS = 2;

	// MAX_ARCHIVE_SIZE is the maximum size possible (the upper bound) of the archive
	const int MAX_ARCHIVE_SIZE = 1000;

	// Crossover Rate and Mutation rate
	const double CROSSOVER_RATE = 0.5;
	const double MUTATION_RATE = 0.08;
	const double HYPERMUTATION_RATE = 0.20;
	const int POPULATION_SIZE = 50;
	const int ELITE_NO = 5;
	const int NUM_OF_ITERATIONS = 500;
	
	// Fitness Threshold
	const double FITNESS_THRESHOLD = 50;

	// Log2(e)
	const double M_LOG2E = 1.44269504088896340736;

/* Debug and Output messages for console */

	// Flags to determine whether the message should be output to the screen
	// Toggle these to control output
	const bool FLAG_OUTOUT_DEBUG = true;
	const bool FLAG_OUTPUT_PRINT = true;

	// Output message type
	enum outputMessageType
	{
		OUTPUT_DEBUG,
		OUTPUT_PRINT
	};

	// Output message function
	void outputMessage(outputMessageType type, std::string message);

#endif