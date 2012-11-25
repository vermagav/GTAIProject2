#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

//Genetic Algorithm V1.0

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <utility>

//Global Constants:
// Number of decision variables
const size_t N_of_x = 30;

// Number of Functions ot be maximized in parallel
const int NO_OBJECTIVE_FUNCTIONS = 2;

//MAX_ARCHIVE_SIZE is the maximum size possible (the upper bound) of the archive
const int MAX_ARCHIVE_SIZE = 1000;

// Define the EPSILON matrix
double EPSILON[NO_OBJECTIVE_FUNCTIONS] = {0.0075, 0.0075};

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
	size_t pathLength;
	size_t binary_length;

	// Cache the values of the objective functions
	double function_value[NO_OBJECTIVE_FUNCTIONS];
	
	// pair of Direction-distance codes
	std::vector<std::pair<int, int> > path;
	
	// x or y monotone
	bool monotone;

	// binary representation as a string
	std::vector<int> binary_rep;

public:
	// parametrized Constructor
	Chromosome(size_t rows, size_t columns): pathLength(rows + columns - 1), binary_length((int)log2(rows + columns))
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

	// Converting from binary_rep to montone/Path and vice-versa
	void encode();
	void decode();
	
	// Used to repair Invalid Paths
	void repair();
	bool isValid() const;
	
	// The two objective functions ot be maximized
	double function1();
	double function2();

	// Function Returns the Fitness of the Chromosome
	double calculateFitness()
	{
		function_value[0]=function1();
		function_value[1]=function2();

		//More Multi-Objective Shit
	}
};

class GeneticAlgorithm
{
public:
	// Generate a random Initial Population
	void generatePopulation(int size, int rows, int colums);

	// Repair Invalid Paths in the Population
	void repairPopulation();

private:
	std::vector<Chromosome> population;
};

#endif