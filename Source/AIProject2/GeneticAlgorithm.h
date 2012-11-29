#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

//Genetic Algorithm V1.0
#include "Chromosome.h"


class GeneticAlgorithm
{
public:
	// Constructor
	GeneticAlgorithm(int size, int r, int c, World *w):crossoverRate(CROSSOVER_RATE), mutationRate(MUTATION_RATE), populationSize(size), world(w), rows(r), columns(c)
	{
		std::cout<<"IN CONSTRUCTOR \n";

		// Where to call generate ??
		generatePopulation();
		//repairPopulation();
		//evaluatePopulationFitness();
	}

	// Generate a random Initial Population
	void generatePopulation();

	// Repair Invalid Paths in the Population
	void repairPopulation();
	
	// Calculate the fitness of each Chromosome in the population and sor Population according to the fitness value
	void evaluatePopulationFitness();
	std::vector<Chromosome> rouletteSelection();
	std::vector<Chromosome> generateOffSpring();
	void run();

	void displayPopulation() const;
	void calculateAverageFitness();
	bool strictDomCheck(int a, int b);
	
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