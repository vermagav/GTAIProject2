#include "GeneticAlgorithm.h"

#include <algorithm>

using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::copy;
using std::back_inserter;
using std::reverse;
using std::cout;
using std::endl;

void GeneticAlgorithm::generatePopulation()
{
	// TODO:: Generate Valid Path
	srand((unsigned)time(0));	

	// First Create N - 2 Random Paths
	int random_num1 = 0, random_num2 = 0;

	// Generate Size - 2 random paths
	for(int i = 0; i != populationSize - 2; i++)
	{
		Chromosome temp(rows, columns, world);
		
		//Set Monotone
		random_num1 = rand()%2;
		temp.setMonotone((bool)random_num1);
		
		// Set path
		// Create Vector to Hold path
		vector<pair<int, int> > temp_path;

		for (int j = 0; j != temp.getPathLength(); j++)
		{
			// Create random no for direction 00, 01, 10, 11
			random_num1 = rand()% 4;

			// Create random no for distance
			random_num2 = rand()%((int)log2(rows));

			//make a pair
			pair<int, int> temp_pair = make_pair(random_num1, random_num2);	

			// Append The pair to the path
			temp_path.push_back(temp_pair);
		}

		// Actually set the path
		temp.setPath(temp_path);
		
		// create the binary Representation
		temp.encode();

		// Add the Randomly Generated Chromosome To the Population
		population.push_back(temp);
	}

	//Add X - Monotone Path to Population
	Chromosome Xmono(rows, columns, world);
	Xmono.setMonotone(false);
	
	// Set the X-monotone path
	vector<pair<int, int> > X_path;
	pair<int, int> temp_pair;

	for (int j = 0; j != Xmono.getPathLength(); j++)
	{
		if(j % 2 == 0)
			temp_pair = make_pair(2, 1);	
		else
			temp_pair = make_pair(0, 1);
		// Append The pair to the path
		X_path.push_back(temp_pair);
	}

	// Actually set the path
	Xmono.setPath(X_path);
	Xmono.encode();
	population.push_back(Xmono);

	//Add Y - Mootone path to Population
	Chromosome Ymono(rows, columns, world);
	Ymono.setMonotone(true);

	//Set the Y - Monotone Path
	vector<pair<int, int> > Y_path;

	for (int j = 0; j != Ymono.getPathLength(); j++)
	{
		if(j % 2 == 0)
			temp_pair = make_pair(2, 1);	
		else
			temp_pair = make_pair(0, 1);
		// Append The pair to the path
		Y_path.push_back(temp_pair);
	}

	// Actually set the path
	Ymono.setPath(X_path);
	
	Ymono.encode();
	population.push_back(Ymono);
}


void GeneticAlgorithm::repairPopulation()
{
	vector<Chromosome> valid, invalid;
	// Repair Invalid Chromosomes
	for(vector<Chromosome>::iterator i = population.begin(); i != population.end(); i++)
		if((*i).isOutOfBounds())
		{
			invalid.push_back((*i));
		}
		else
		{
			valid.push_back((*i));
		}

	for(vector<Chromosome>::iterator i = invalid.begin(); i != invalid.end(); i++)
		(*i).repairOutofBounds();

	population.clear();
	copy(valid.begin(), valid.end(), back_inserter(population));
	copy(invalid.begin(), invalid.end(), back_inserter(population));

	//?? Call fitness functions
}


void GeneticAlgorithm::displayPopulation() const
{
	// Display the entire populatoion
	for(vector<Chromosome>::const_iterator i = population.begin(); i != population.end(); i++)
	{
		(*i).display();
		cout<<endl;
	}
}

void GeneticAlgorithm::evaluatePopulationFitness()
{
	for(vector<Chromosome>::iterator i = population.begin(); i != population.end(); i++)
	{
		(*i).calculateFitness();
	}

	// Sort the population according to the fitness evaluation
	sort(population.begin(), population.end(), compare);
}

void GeneticAlgorithm::calculateAverageFitness()
{
	double sum = 0.0;

	for(vector<Chromosome>::const_iterator i = population.begin(); i != population.end(); i++)
		sum += (*i).getFitness();

	sum /=population.size();

	// Set the average population for Hyper Mutation
	averagePopulationFitness = sum;
}

std::vector<Chromosome> GeneticAlgorithm::rouletteSelection()
{
	// Group of Chromsomes: Sent to the next genration without crossover and Mutation
	vector<Chromosome> bestChromosomes;

	// Probability of Selection
	vector<pair<Chromosome, double> > probOfSelection;

	double fitnesssum = 0.0;
	double probabilitysum = 0.0;
	double probability = 0.0;
	
	// Calculate the sum
	for(vector<Chromosome>::const_iterator i = population.begin(); i != population.end(); i++)
		fitnesssum += (*i).getFitness();

	// Get the roulette probability 
	for(vector<Chromosome>::const_iterator i = population.begin(); i != population.end(); i++)
	{
		probability = probabilitysum + ((*i).getFitness()/fitnesssum);
		probabilitysum += probability;
		probOfSelection.push_back(make_pair((*i), probabilitysum));
	}

	// Generate a number between 0 and 1
	double r = 0;
	int count = 0;


	while (count != (POPULATION_SIZE *CROSSOVER_RATE))
	{
		// Generate a random number between 0 and 1 
		r = ((double) rand() / (RAND_MAX));

		for(vector<pair<Chromosome, double> >::const_iterator i = probOfSelection.begin(); i != probOfSelection.end(); i++)
			if(r > (*i).second)
			{
				// && r > (*(i +1)).second ??
				bestChromosomes.push_back((*i).first);
				count++;
				break;
			}	
	}

	return bestChromosomes;
}


std::vector<Chromosome> GeneticAlgorithm::generateOffSpring()
{
	// To hold the Offsprings
	vector<Chromosome> offsprings;

	// Probability of Selection
	vector<pair<Chromosome, double> > probOfSelection;

	double fitnesssum = 0.0;
	double probabilitysum = 0.0;
	double probability = 0.0;
	
	// Calculate the sum
	for(vector<Chromosome>::const_iterator i = population.begin(); i != population.end(); i++)
		fitnesssum += (*i).getFitness();

	// Get the roulette probability 
	for(vector<Chromosome>::const_iterator i = population.begin(); i != population.end(); i++)
	{
		probability = probabilitysum + ((*i).getFitness()/fitnesssum);
		probabilitysum += probability;
		probOfSelection.push_back(make_pair((*i), probability));
	}

	// Generate a number between 0 and 1
	double r1 = 0;
	double r2 = 0;
	int count = 0;

	while (count != (POPULATION_SIZE *(1 - CROSSOVER_RATE) - 2 * ELITE_NO))
	{
		// Generate a random number between 0 and 1 
		r1 = ((double) rand() / (RAND_MAX));
		r2 = ((double) rand() / (RAND_MAX));

		bool selected1 = false, selected2 = false;

		Chromosome temp1(LEVEL_NUM_ROWS, LEVEL_NUM_COLUMNS, world);
		Chromosome temp2(LEVEL_NUM_ROWS, LEVEL_NUM_COLUMNS, world);

		for(vector<pair<Chromosome, double> >::const_iterator i = probOfSelection.begin(); i != probOfSelection.end(); i++)
		{
			if(r1 > (*i).second && r1 < (*(i + 1)).second)
			{
				temp1 = ((*i).first);
				selected1 = true;
			}
		
			if(r2 > (*i).second && r2 < (*(i + 1)).second)
			{
				temp2 = ((*i).first);
				selected2 = true;
			}

			if(selected1 && selected2)
			{
				break;
				count++;
			}	
		}

		offsprings.push_back(crossover(temp1, temp2));
	}

	return offsprings;
}

void GeneticAlgorithm::run(int size, int rows , int columns, World* world)
{
	// Generate the initial Population
	generatePopulation();

	// Try to Repair the Invalid paths
	repairPopulation();

	// Calculate the fitness of each chromosome in the population and sort
	evaluatePopulationFitness();

	//----------------------------------------------------------------------
	// Elitist Strategy Used
	// Should go in a loop

	// Get the Best ELITE_NO of Chromosomes
	vector<Chromosome> bestChromosomes(population.begin(), population.begin() + ELITE_NO);
	
	// Generate Elite Number of Chromsomes form the elite population
	vector<Chromosome> newEliteGeneration;
	for(int i =0; i != ELITE_NO; i++)
	{
		// Select two random Chromsomes from bestChromosomes and Mate them and Mutate them
		Chromosome temp = crossover(population[rand() % bestChromosomes.size()], population[rand() % bestChromosomes.size()]);
		mutate(temp);

		// Add to new generation
		newEliteGeneration.push_back(temp);
	}

	// Use Roulette Selcetion to select MUTATION_RATE*POPULATION_SIZE
	vector<Chromosome> rouletteChromosomes = rouletteSelection();
	
	// Remove worst ELITE_NO chromsomes
	int offset = population.size() - ELITE_NO;
	population.erase(population.begin() + offset, population.end());

	// Remove ELITE_NO Best Chromosmes
	population.erase(population.begin(), population.begin() + ELITE_NO);
		
	vector<Chromosome> offsprings = generateOffSpring();
	
	// NEW POPULATION
	population.clear();
	copy(bestChromosomes.begin(), bestChromosomes.end(), back_inserter(population));
	copy(newEliteGeneration.begin(), newEliteGeneration.end(), back_inserter(population));
	copy(rouletteChromosomes.begin(), rouletteChromosomes.end(), back_inserter(population));
	// Try to Repair the Invalid paths
	repairPopulation();

	// Calculate the fitness of each chromosome in the population and sort
	evaluatePopulationFitness();

	// HYPERMUTATION CHECK
	if(population[0].getFitness() < FITNESS_THRESHOLD)
		mutationRate = HYPERMUTATION_RATE;
		// reduce mutation rate
}