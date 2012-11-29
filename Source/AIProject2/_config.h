/*
 * Configuration Settings for the Project
 * Ideally, these should be imported from a .ini file
 */
#ifndef _CONFIG_H
#define _CONFIG_H

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
const int ENEMY_GENERATION_BUFFER = 10;

// World's Game State
enum GameState
{
	GAMESTATE_RUNNING,
	GAMESTATE_FAIL,
	GAMESTATE_WIN,
	GAMESTATE_COUNT
};

// Step size for home agent and adversary
const int STEP_SIZE_HOMEAGENT = 4;
const int STEP_SIZE_ADVERSARY = 1;

// Start position of home agent
const int STARTX_HOMEAGENT = 0;
const int STARTY_HOMEAGENT = 0;
const int STARTX_GOAL = 140;
const int STARTY_GOAL = 48;

// Boundary constants for the level
const int LEVEL_MIN_X = 0;
const int LEVEL_MAX_X = 140;
const int LEVEL_MIN_Y = 0;
const int LEVEL_MAX_Y = 70;

// Maximum number of rows (depends on Y) and columns (depends on X)
const int LEVEL_NUM_ROWS = (LEVEL_MAX_Y - LEVEL_MIN_Y) + 1;
const int LEVEL_NUM_COLUMNS = (LEVEL_MAX_X - LEVEL_MIN_X) + 1;

// Number of enemies
const int NUM_ENEMIES = 20;

// Number of moves per second
const int NUM_MOVES_PER_SEC = 1;

// Difficulty mode for adversary's movement
enum DifficultyMode
{
	RANDOM_EASY,
	RANDOM_NORMAL,
	RANDOM_INTELLIGENT,
	NUM_OF_MODES
};

// Change this to alter the current difficulty
const DifficultyMode CURRENT_DIFFICULTY = RANDOM_EASY;

/* Algorithm Related Config */

	// Radius Computation Buffer
	const int RADIUS_BUFFER = 10;
	// Victory Check Buffer Radius
	const int WIN_BUFFER = 3;
	// Node Heuristic Weightage: Distance from <Home Agent> to <Path Node>
	const double NODE_WEIGHTAGE_D1 = 0.45;
	// Node Heuristic Weightage: Distance from <Path Node> to <Goal>
	const double NODE_WEIGHTAGE_D2 = 0.55;

#endif