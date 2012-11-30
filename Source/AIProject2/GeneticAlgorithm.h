#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

//Genetic Algorithm V1.0
#include "Chromosome.h"
#include <conio.h>

class GeneticAlgorithm
{
public:
	// Constructor
	GeneticAlgorithm(int size, int r, int c, World *w):crossoverRate(CROSSOVER_RATE), mutationRate(MUTATION_RATE), averagePopulationFitness(0), world(w), populationSize(size), rows(r), columns(c)
	{
		//std::cout<<"IN CONSTRUCTOR \n";
	}

	// Generate the entire population randomly, repair it and calculate its fitness
	void initAlgorithm()
	{
		std::cout<<"\nGenerating Population...\n\n";
		generatePopulation();
		getch();

		std::cout<<"\nPopulation completely generated...";
		std::cout<<"\nPress any key to repair population.";
		getch();

		std::cout<<"\nRepairing population...";
		repairPopulation();
		std::cout<<"\nPopulation repaired.";
		std::cout<<"\nPress any key to evaluate fitness.";
		getch();

		evaluatePopulationFitness();
		std::cout<<"\nFitness evaluated! Genetic algorithm completely initialized.";
		getch();
	}
	
	// Generate a random Initial Population
	void generatePopulation();

	// Repair Invalid Paths in the Population
	void repairPopulation();
	
	// Calculate the fitness of each Chromosome in the population and sort Population according to the fitness value
	void evaluatePopulationFitness();

	// Returns the Best Chromosomes using roulette selection to move directly to the next generation
	std::vector<Chromosome> rouletteSelection();
	
	// Uses Roulette Selection to select Parents based on Fitness and produce offsprings
	std::vector<Chromosome> generateOffSpring();
	
	// The main function that runs the genetic algorithm
	void run();

	// Other Utility Functions required by the run function
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