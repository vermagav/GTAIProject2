#include "GeneticAlgorithm.h"
#include <algorithm>

using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::copy;
using std::back_inserter;
using std::reverse;

// Utility Function: get vector of binary form from the Number
vector<int> getBinaryForm(int number, int vector_size)
{
	vector<int> result;
	int remainder = 0, count = 0;

	// Store the Binary Bits in the Vector
	while(number > 0)
	{
		remainder=number % 2;	
		number = number / 2;
		result.push_back(remainder);
		count++;
    }
	
	// Fill in the remaining Zeros
	while(count != vector_size - 1)
		result.push_back(0);

	//reverse the vector
	reverse(result.begin(), result.end());
			
	return result;
}

// Utility Function: get number from vector of binary form 
int getIntegerForm(vector<int> binary)
{
	int result = 0;
	
	for(size_t i = 0; i != binary.size(); i++)
		result += (binary[i] * pow(2, i));

	return result;
}

void Chromosome::encode()
{
	// Clear the previous Binary Representation
	binary_rep.clear();

	// Set whether X or Y monotone
	binary_rep.push_back((int)monotone);

	//Set the Path
	for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
	{
		if((*i).first == 0)
		{
			binary_rep.push_back(0);
			binary_rep.push_back(0);
		}
		
		if((*i).first == 1)
		{
			binary_rep.push_back(0);
			binary_rep.push_back(1);
		}
		
		if((*i).first == 2)
		{
			binary_rep.push_back(1);
			binary_rep.push_back(0);
		}
			
		if((*i).first == 3)
		{
			binary_rep.push_back(1);
			binary_rep.push_back(1);
		}
			
		// Convert the distance to binary form;
		// Binary Form hs to be Proper Length
		int int_dist = (*i).second;
		if( int_dist < 0)
		{
			binary_rep.push_back(1);
			int_dist *= (-1);
		}
		else
			binary_rep.push_back(0);

		vector<int> distance = getBinaryForm(int_dist, binary_length);

		// Make Sure Length of distance vector is binary_length 
		//Append that to the end of the binary_rep
		copy(distance.begin(), distance.end(), back_inserter(binary_rep));
	}
}

void Chromosome::decode()
{
	// Set Monotone
	monotone = (bool)binary_rep[0];
	
	// Clear Exisitng Path
	path.clear();

	// Get new Path
	//Use While Loop...Get rid of For Loop
	vector<int>::const_iterator i = binary_rep.begin() + 1;

	while(i < binary_rep.end())
	{
		pair<int, int> temp;

		if( ((*i) == 0) && ((*(i + 1) == 0)) )
		{
			//get number from the next binary_length
			vector<int> bin_distance(i + 3, i + 3 + binary_length);			
			int distance = getIntegerForm(bin_distance);
			
			// if Number is negative
			if((*(i + 2) == 1))
				distance *= (-1);

			// make the pair
			temp = make_pair(0, distance);
		}

		if( ((*i) == 0) && ((*(i + 1) == 1)) )
		{
			// disregard the number of length log2(pathlength)???
			temp = make_pair(1, 1);
		}

		if( ((*i) == 1) && ((*(i + 1) == 0)) )
		{
			// disregard the number of length log2(pathlength)???
			temp = make_pair(2, 1);
		}

		if( ((*i) == 1) && ((*(i + 1) == 1)) )
		{
			//get number from the next log2(pathlength) ????
			temp = make_pair(3, 1);
		}

		i += (3 + binary_length);
		path.push_back(temp);
	}
}

void Chromosome::repair()
{
	// Repair paths that have a Solid Obstacle: Don't Know How To
	// Repair paths that go Outside The Level, wherever they go out of the level: straight line path to the goal
	// Repair paths that do not end in destination cell, continue straight line path
}

bool Chromosome::isValid() const
{
	// TODO
	return true;
}

void GeneticAlgorithm::generatePopulation(int size, int rows , int columns)
{
	srand((unsigned)time(0));	

	// First Create N - 2 Random Paths
	int random_num1 = 0, random_num2 = 0;

	for(int i = 0; i != size - 2; i++)
	{
		Chromosome temp(rows, columns);
		
		//Set Monotone
		random_num1 = rand()%2;
		temp.setMonotone((bool)random_num1);
		
		// Set path
		// Create Vector to Hold path
		vector<pair<int, int> > temp_path;

		for (int j = 0; j != temp.getPathLength(); j++)
		{
			// Create random no for direction 00, 01, 10, 11
			random_num1 = rand()%3;

			// Create random no for distance
			random_num2 = rand()%((int)log2(rows + columns));

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
	Chromosome Xmono(rows, columns);
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
	Chromosome Ymono(rows, columns);
	Ymono.setMonotone(true);

	//Set the Y - Monotone Path
	vector<pair<int, int> > Y_path;

	for (int j = 0; j != Ymono.getPathLength(); j++)
	{
		if(j%2 == 0)
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
	// Repair Invalid Chromosomes
	for(vector<Chromosome>::iterator i = population.begin(); i != population.end(); i++)
		if((*i).isValid())
			(*i).repair();
}