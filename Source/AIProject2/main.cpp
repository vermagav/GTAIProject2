/*
 * @Purpose: Home of the main() function
 * 
 */
#include "_config.h"
#include "World.h"
#include "GeneticAlgorithm.h"
#include <conio.h>

using namespace std;

int main()
{
	// Initialize world object
	World* world;
	world = new World();

	// Initialize level representation
	world->initWorld();

	cout<<"\nWorld initiated...";
	cout<<"\nLevel procedurally generated...";
	cout<<"\nTextual representation of level:";

	cout<<"\n\n";

	// Render world
	world->drawWorld();

	cout<<"\n\nPress any key to continue.";
	getch();

	// Initalize genetic algorithm
	GeneticAlgorithm genetic(POPULATION_SIZE, LEVEL_NUM_ROWS, LEVEL_NUM_COLUMNS, world);
	genetic.initAlgorithm();

	cout<<"\nGenetic Algorithm initialized...";
	cout<<"\nPress any key to generate population.";
	getch();
	
	// Display initial population
	genetic.displayPopulation();
	getch();

	// Delete world population
	delete world;
	
	return 0;
}