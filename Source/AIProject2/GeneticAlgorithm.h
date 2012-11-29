#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

//Genetic Algorithm V1.0
#include "Chromosome.h"


class GeneticAlgorithm
{
public:
	// Constructor
	GeneticAlgorithm(int size, int r, int c):crossoverRate(CROSSOVER_RATE), mutationRate(MUTATION_RATE), populationSize(size), rows(r), columns(c)
	{
		// Where to call generate

	}

	// Generate a random Initial Population
	void generatePopulation();

	// Repair Invalid Paths in the Population
	void repairPopulation();
	
	// Calculate the fitness of each Chromosome in the population and sor Population according to the fitness value
	void evaluatePopulationFitness();
	std::vector<Chromosome> rouletteSelection();
	std::vector<Chromosome> generateOffSpring();
	void run(int size, int rows , int columns, World* world);

	void displayPopulation() const;
	void calculateAverageFitness();

private:
	std::vector<Chromosome> population;
	double crossoverRate;
	double mutationRate;
	double averagePopulationFitness;
	World *world;
	int populationSize;
	int rows, columns;
};

#endif