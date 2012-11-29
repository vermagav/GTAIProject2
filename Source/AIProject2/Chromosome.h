#ifndef CHROMOSOME_H
#define CHROMOSOME_H

// Chromosome.h - v1.0

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <utility>
#include "World.h"

// Number of Functions ot be maximized in parallel
const int NO_OBJECTIVE_FUNCTIONS = 2;

//MAX_ARCHIVE_SIZE is the maximum size possible (the upper bound) of the archive
const int MAX_ARCHIVE_SIZE = 1000;

// Crossover Rate and Mutation rate
const double CROSSOVER_RATE = 0.5;
const double MUTATION_RATE = 0.08;
const double HYPERMUTATION_RATE = 0.20;
const int POPULATION_SIZE = 50;
const int ELITE_NO = 5;
const int NUM_OF_ITERATIONS = 500;
// TODO: Needs to be changed
const double FITNESS_THRESHOLD = 50;

const double M_LOG2E = 1.44269504088896340736; //log2(e)

inline double log2(const long double x){
    return  log(x) * M_LOG2E;
}

/*
Chromosome structure is a binary string representation of monotone paths. The binary string chromosome is made up
of n − 1 (where n is the number of columns and rows in the grid representing the map of a given terrain) pairs of direction/
distance of length 3+log[2]n, and an extra bit a which determines if the path is x-monotone (a = 0) or y-monotone
(a = 1). And each pair of direction/distance codes the direction in which a robot moves inside the grid and the number of
cells it moves through in that direction. The meaning of the bits in each pair of direction/distance is given in Tables 1 and 2.
*/

class Chromosome
{
private:
	int pathLength;
	int binary_length;
	
	int rank;

	// Cache the values of the objective functions
	double function_value[NO_OBJECTIVE_FUNCTIONS];
	
	// pair of Direction-distance codes
	std::vector<std::pair<int, int> > path;
	
	// x or y monotone
	bool monotone;

	// binary representation as a string
	std::vector<int> binary_rep;
	
	// Pointer to the World Object to get Level
	World *world;  

public:
	// parametrized Constructor
	// check all the ns....
	// make no. of rows or column same
	Chromosome(size_t rows, size_t columns, World* w): pathLength(rows + columns - 1), binary_length((int)log2(rows)), world(w)
	{
		// Set the Total Length of the Path in Construcutor List
		// Set the Length of Binary format of Distance associated with the Direction in Constructor List

		// Set function values to 0
		for(int i = 0; i != NO_OBJECTIVE_FUNCTIONS; i++)
			function_value[i] = 0;
	}

	inline std::vector<int> getBinaryRep() const
	{
		return binary_rep;
	}
	
	inline void setBinaryRep(std::vector<int> b)
	{
		binary_rep = b;
	}

	inline bool getMonotone() const
	{
		return monotone;
	}

	inline void setMonotone(bool m)
	{
		monotone = m;
	}

	inline void setPath(std::vector<std::pair<int, int> > p)
	{
		path = p;
	}
	
	inline size_t getPathLength()
	{
		return pathLength;
	}

	inline int getRank() const
	{
		return rank;
	}

	void setRank(int r)
	{
		rank = r;
	}

	double* getFunctionValue()
	{
		return function_value;
	}

	double getFitness()
	{
		return (function_value[0] + function_value[1]);
	}

	int getbinaryLength() const
	{
		return binary_length;
	}

	// Converting from binary_rep to montone/Path and vice-versa
	void encode();
	void decode();
	
	// Used to repair Invalid Paths
	void repairOutofBounds();
	void repairSolidObstacles();

	// validity Check functions
	bool isValid() const;

	bool isOutOfBounds() const;
	int noOfObstacle() const;
	bool goesThruGoal() const;

	// The two objective functions to be maximized
	void function1();
	void function2();

	//display binary Representation of the Chromosome
	void display() const;

	// Function Returns the Fitness of the Chromosome
	void calculateFitness()
	{
		function1();
		function2();
	}
};

// Forward Declarations of Functions
bool compare(Chromosome a, Chromosome b);
Chromosome crossover(const Chromosome &a, const Chromosome &b);
void mutate(Chromosome &a);

#endif
