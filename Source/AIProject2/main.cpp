/*
 * @Purpose: Home of the main() function
 * 
 */
#include "_config.h"
#include "World.h"
#include "GeneticAlgorithm.h"
#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	World* world;
	world = new World();
	world->initWorld();
	

	cout<<"LOG of 16"<<log2(16);
	
	vector<int> bin_num = getBinaryForm(9, log2(16));

	for(vector<int>::size_type i = 0; i != bin_num.size(); i++)
		cout<<bin_num[i];
	cout<<endl;
	
	int number = getIntegerForm(bin_num);

	cout<<number;

	getch();

	//world->drawWorld();
	/*
	GeneticAlgorithm genetic(POPULATION_SIZE, LEVEL_NUM_ROWS, LEVEL_NUM_COLUMNS, world);
	
	genetic.displayPopulation();
	getch();

	delete world;
	/*
	char key = '\0';

	while(key != 'q')
	{
		world = new World();
		world->initWorld();
		world->drawWorld();
		std::cout<<"\n\n\n\t[Q]uit";
		key = getch();
	}

	delete world;
	*/
	return 0;
}