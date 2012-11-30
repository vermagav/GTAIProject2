#ifndef CHROMOSOME_H
#define CHROMOSOME_H

// Chromosome.h - v1.0

#include "_config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <utility>
#include "World.h"

inline double log2(const long double x){
    return  log(x) * M_LOG2E;
}

/*
 * Chromosome structure is a binary string representation of monotone paths. The binary string chromosome is made up
 * of n − 1 (where n is the number of columns and rows in the grid representing the map of a given terrain) pairs of direction/
 * distance of length 3+log[2]n, and an extra bit a which determines if the path is x-monotone (a = 0) or y-monotone
 * (a = 1). And each pair of direction/distance codes the direction in which a robot moves inside the grid and the number of
 * cells it moves through in that direction. The meaning of the bits in each pair of direction/distance is given in Tables 1 and 2.
 */

class Chromosome
{
private:
	int pathLength;
	int binaryLength;
	
	// Pareto Optimality rank of the chromosome
	int rank;

	// Cache the values of the objective functions
	double function_value[NO_OBJECTIVE_FUNCTIONS];
	
	// Pair of {Direction, Distance} codes
	std::vector<std::pair<int, int> > path;
	
	// x or y monotone
	bool monotone;

	// Binary representation as a string
	std::vector<int> binary_rep;
	
	// Pointer to the World Object to get Level
	World *world;

public:
	// Parametrized Constructor
	// make num of rows or column the same
	Chromosome(size_t rows, size_t columns, World* w): pathLength(rows + columns - 1), binaryLength((int)log2(rows)), world(w)
	{
		// Set the Total Length of the Path in Construcutor List
		// Set the Length of Binary format of Distance associated with the Direction in Constructor List

		// Set function values to 0
		for(int i = 0; i != NO_OBJECTIVE_FUNCTIONS; i++)
			function_value[i] = 0;
	}

	// Set and Get functions
	inline std::vector<int> getBinaryRep() const { return binary_rep; }
	inline void setBinaryRep(std::vector<int> b) { binary_rep = b; }
	inline bool getMonotone() const { return monotone; }
	inline void setMonotone(bool m) { monotone = m;	}
	inline void setPath(std::vector<std::pair<int, int> > p) { path = p; }
	inline size_t getPathLength() {	return pathLength; }
	inline int getRank() const { return rank; }
	void setRank(int r) { rank = r; }
	double* getFunctionValue() { return function_value; }
	double getFitness() { return (function_value[0] + function_value[1]); }
	int getbinaryLength() const { return binaryLength; }

	// Converting from binary_rep to montone/Path and vice-versa
	void encode();
	void decode();
	
	// Used to repair invalid Paths
	void repairOutofBounds();
	void repairSolidObstacles();

	// Validity check functions
	bool isValid() const;
	bool isOutOfBounds() const;
	int numOfObstacles() const;
	bool goesThruGoal() const;

	// The two objective functions to be maximized
	void fitnessFunctionLength();
	void fitnessFunctionSafety();

	// Display binary representation of the chromosome
	void display() const;

	// Function calculates the fitness of the chromosome
	void calculateFitness()
	{
		fitnessFunctionLength();
		fitnessFunctionSafety();
	}
};

// Forward Declarations of Functions
bool compare(Chromosome a, Chromosome b);
Chromosome crossover(const Chromosome &a, const Chromosome &b);
void mutate(Chromosome &a);
std::vector<int> getBinaryForm(int number, int vector_size);
int getIntegerForm(vector<int> binary);

#endif
