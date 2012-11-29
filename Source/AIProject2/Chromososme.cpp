#include "Chromosome.h"
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

//--------------------------------------------
// TODO X AND Y ROWCOLUMN SHIT!!!!!
// Utility Function: get vector of binary form from the Number
vector<int> getBinaryForm(int number, int vector_size)
{
	cout<<"\n Number given to func ="<<number<<"\n";

	vector<int> result;
	int remainder = 0, count = 0;

	// Store the Binary Bits in the Vector
	while(number > 0)
	{
		remainder=number % 2;	
		number = number / 2;
		result.push_back(remainder);
		count++;
		cout<<number;
    }
	
	cout<<" \ncount "<<count<<count<<"\nsize "<<vector_size;
	
	// Fill in the remaining Zeros
	// Check -1???
	while(count != vector_size)
	{
		result.push_back(0);
		count++;
	}

	//reverse the vector
	reverse(result.begin(), result.end());
			
	return result;
}

// Utility Function: get number from vector of binary form 
int getIntegerForm(vector<int> binary)
{
	int result = 0;
	
	for(size_t i = 0; i != binary.size(); i++)
		result += (binary[i] * (int)pow(2, i));

	return result;
}
//_______________________________________________________________________________________________________________


bool compare(Chromosome a, Chromosome b)
{
	// Compare Fitness for sorting into decreasing order for fitness evaluations
	return a.getRank() > b.getRank();
}

// Crossover and Mutate Functions

Chromosome crossover(const Chromosome &a, const Chromosome &b)
{
	// Create the offspring
	Chromosome offspring(a);

	// Get the Binary Representations for the two Chromosomes
	vector<int> bitRep1 = a.getBinaryRep();
	vector<int> bitRep2 = b.getBinaryRep();

	// USE CROSSOVER_RATE??
	// Generate a random  point in range as the Cross-Over Point
	int randNo = rand()%bitRep1.size();

	// Get the crossovered bit representations
	vector<int> offspringRep(bitRep1.begin(), bitRep1.begin() + randNo);
	copy(bitRep2.begin() + randNo, bitRep2.end(), back_inserter(offspringRep));
	
	// Assign the new representation to the offspring
	offspring.setBinaryRep(offspringRep);
	offspring.decode();
	offspring.calculateFitness();

	return offspring;
}

// Single Bit Binary Mutation
void mutate(Chromosome &a)
{
	
	
	// Decide to Mutate or Not Mutate
	if( (rand() % 100) > MUTATION_RATE)
	{
		// Get the Binary Representation and Mutate at a Random Index 
		vector<int> binaryRep = a.getBinaryRep();

		int randomNo = rand() % binaryRep.size();

		if(binaryRep[randomNo] == 0)
			binaryRep[randomNo] = 1;
		else
			binaryRep[randomNo] = 0;

		a.setBinaryRep(binaryRep);
	}
}

//_______________________________________________________________________________________________________________
void Chromosome::encode()
{
	// Clear the previous Binary Representation
	binary_rep.clear();

	// Set whether X or Y monotone
	binary_rep.push_back((int)monotone);

	cout<<"MONOTONE SET";
	cout<<"monotne"<< monotone;
	cout<<"path:"<<path.size();

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
		
		cout<<"distance = "<<int_dist;

		if( int_dist < 0)
		{
			binary_rep.push_back(1);
			int_dist *= (-1);
		}
		else
			binary_rep.push_back(0);

		cout<<"PUSHED PATH CODE BUT NOT DISTANCE";

		cout<<"Length of Binary path"<< binary_length;

		vector<int> distance = getBinaryForm(int_dist, binary_length);

		cout<<"done distance";

		// Make Sure Length of distance vector is binary_length 
		//Append that to the end of the binary_rep
		copy(distance.begin(), distance.end(), back_inserter(binary_rep));
		
		cout<<"1 path-code done";
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

bool Chromosome::isOutOfBounds() const
{
	// Make sure decode is called before calling this
	// decode();
	// xLevel and yLevel to maintain actual path in the level
	int xLevel = 0, yLevel = 0;

	
	if(monotone)
	{
		// Y - Monotone path
		for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
		{
			if((*i).first == 0)
			{
				// Save Previous xlevel
				int xPrevLevel = xLevel;

				// Move Horziontally by (second) distance
				xLevel += (*i).second;

				for(int j = xPrevLevel; j <= xLevel; j++)
					if(j == STARTX_GOAL && yLevel == STARTY_GOAL)
						return false;
			}
			if((*i).first == 1)
			{
				// Move Diagonally Left
				xLevel -= 1;
				yLevel += 1;
			
			}
			
			if((*i).first == 2)
			{
				// Move vertically downwards
				yLevel += 1;
			}

			if((*i).first == 3)
			{
				// Move Diagonally Right
				xLevel += 1;
				yLevel += 1;
			}

			if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
				return false;

			// Out of Bounds Check
			if((xLevel < 0) || (xLevel > LEVEL_MAX_X) || (yLevel < 0) || (yLevel > LEVEL_MAX_Y))
				return true;
		}
	}
	else
		{
			// X - Monotone Path
			for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
			{
				if((*i).first == 0)
				{
					// Save Previous xlevel
					int yPrevLevel = yLevel;

					// Move Vertically by (second) distance
					yLevel += (*i).second;

					for(int j = yPrevLevel; j <= yLevel; j++)
						if(xLevel == STARTX_GOAL && j == STARTY_GOAL)
							return false;
				}
				if((*i).first == 1)
				{
					// Move Diagonally UP
					xLevel += 1;
					yLevel -= 1;
			
				}
			
				if((*i).first == 2)
				{
					// Move Horizontally Forward
					xLevel += 1;
				}

				if((*i).first == 3)
				{
					// Move Diagonally Down
					xLevel += 1;
					yLevel += 1;
				}
			
				if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
					return false;

				// Out of Bounds Check, after every move according to path
				if((xLevel < 0) || (xLevel > LEVEL_MAX_X) || (yLevel < 0) || (yLevel > LEVEL_MAX_Y))
					return true;
			}
		}
	
	// if xLevel and yLevel are still in bounds
	return false;
}


int Chromosome::noOfObstacle() const
{
	// Make sure decode is called before calling this
	// decode();
	// xLevel and yLevel to maintain actual path in the level
	int xLevel = 0, yLevel = 0, obstacleCount = 0;

	if(monotone)
	{
		// Y - Monotone path
		for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
		{
			if((*i).first == 0)
			{
				// Save Previous xlevel
				int xPrevLevel = xLevel;

				// Move Horziontally by (second) distance
				xLevel += (*i).second;

				for(int j = xPrevLevel; j <= xLevel; j++)
					if(j == STARTX_GOAL && yLevel == STARTY_GOAL)
						return obstacleCount;
					else
						if(world->getLevel().getPoint(j, yLevel).getType() == TYPE_OBSTACLE)
							obstacleCount++;

			}
			if((*i).first == 1)
			{
				// Move Diagonally Left
				xLevel -= 1;
				yLevel += 1;

				if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
					return obstacleCount;
				if(world->getLevel().getPoint(xLevel, yLevel).getType() == TYPE_OBSTACLE)
					obstacleCount++;
			}
			
			if((*i).first == 2)
			{
				// Move vertically downwards
				yLevel += 1;

				if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
					return obstacleCount;
				if(world->getLevel().getPoint(xLevel, yLevel).getType() == TYPE_OBSTACLE)
					obstacleCount++;
			}

			if((*i).first == 3)
			{
				// Move Diagonally Right
				xLevel += 1;
				yLevel += 1;

				if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
					return obstacleCount;
				if(world->getLevel().getPoint(xLevel, yLevel).getType() == TYPE_OBSTACLE)
					obstacleCount++;
			}
		}
	}
	else
		{
			// X - Monotone Path
			for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
			{
				if((*i).first == 0)
				{
					// Save Previous xlevel
					int yPrevLevel = yLevel;

					// Move Vertically by (second) distance
					yLevel += (*i).second;

					for(int j = yPrevLevel; j <= yLevel; j++)
						if(xLevel == STARTX_GOAL && j == STARTY_GOAL)
							return obstacleCount;
						else
							if(world->getLevel().getPoint(xLevel, j).getType() == TYPE_OBSTACLE)
								obstacleCount++;
				}
				if((*i).first == 1)
				{
					// Move Diagonally UP
					xLevel += 1;
					yLevel -= 1;

					if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
						return obstacleCount;
					if(world->getLevel().getPoint(xLevel, yLevel).getType() == TYPE_OBSTACLE)
						obstacleCount++;
				}
			
				if((*i).first == 2)
				{
					// Move Horizontally Forward
					xLevel += 1;

					if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
						return obstacleCount;
					if(world->getLevel().getPoint(xLevel, yLevel).getType() == TYPE_OBSTACLE)
						obstacleCount++;
				}

				if((*i).first == 3)
				{
					// Move Diagonally Down
					xLevel += 1;
					yLevel += 1;

					if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
						return obstacleCount;
					if(world->getLevel().getPoint(xLevel, yLevel).getType() == TYPE_OBSTACLE)
						obstacleCount++;
				}
			}
		}

	return obstacleCount;
}

bool Chromosome::goesThruGoal() const
{
	// Make sure decode is called before calling this
	// decode();
	// xLevel and yLevel to maintain actual path in the level
	int xLevel = 0, yLevel = 0;

	if(monotone)
	{
		// Y - Monotone path
		for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
		{
			if((*i).first == 0)
			{
				// Save Previous xlevel
				int xPrevLevel = xLevel;

				// Move Horziontally by (second) distance
				xLevel += (*i).second;

				for(int i = xPrevLevel; i <= xLevel; i++)
					if(i == STARTX_GOAL && yLevel == STARTY_GOAL)
						return true;
			}

			if((*i).first == 1)
			{
				// Move Diagonally Left
				xLevel -= 1;
				yLevel += 1;
			}
			
			if((*i).first == 2)
			{
				// Move vertically downwards
				yLevel += 1;
			}

			if((*i).first == 3)
			{
				// Move Diagonally Right
				xLevel += 1;
				yLevel += 1;
			}

			if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
				return true;
		}
	}
	else
		{
			// X - Monotone Path
			for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
			{
				if((*i).first == 0)
				{
					// Save Previous xlevel
					int yPrevLevel = yLevel;

					// Move Vertically by (second) distance
					yLevel += (*i).second;

					for(int j = yPrevLevel; j <= yLevel; j++)
						if(xLevel == STARTX_GOAL && j == STARTY_GOAL)
							return true;
				}

				if((*i).first == 1)
				{
					// Move Diagonally UP
					xLevel += 1;
					yLevel -= 1;
				}
			
				if((*i).first == 2)
				{
					// Move Horizontally Forward
					xLevel += 1;
				}

				if((*i).first == 3)
				{
					// Move Diagonally Down
					xLevel += 1;
					yLevel += 1;
				}

				if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
					return true;
			}
		}

	// Returns if it ends at the Goal or Not
	if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
		return false;
	else
		return true;
}

void Chromosome::function1()
{
	// PATH LENGTH FITNESS FUNCTION: Smaller path.. Higher fitness

	// Assign a Low fitness value to an Out of Bound Paths
	if(isOutOfBounds())
		function_value[0] = 1;
	
	int length = 0, obstacleCount = 0;
	
	for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
		if((*i).first == 0)
			length += abs((*i).second);
		else
			length += 1;

	// Get the Number of Obstacles
	obstacleCount = noOfObstacle();

	// Assign Low Score if path has obstacles
	if(obstacleCount == 0)
		function_value[0] = (double)((pathLength + 1)*(pathLength + 1) - length);
	else
		function_value[0] = ((double)(pathLength + 1)*(pathLength + 1) - length)/obstacleCount;
}

void Chromosome::function2()
{
	// Safety FITNESS Function
	double safetyValue = 0;

	// Make sure decode is called before calling this
	// decode();
	// xLevel and yLevel to maintain actual path in the level
	int xLevel = 0, yLevel = 0;

	if(monotone)
	{
		// Y - Monotone path
		for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
		{
			if((*i).first == 0)
			{
				// Save Previous xlevel
				int xPrevLevel = xLevel;

				// Move Horziontally by (second) distance
				xLevel += (*i).second;

				for(int i = xPrevLevel; i <= xLevel; i++)
					safetyValue +=  world->getLevel().getPoint(i, yLevel).getDifficulty();
			}

			if((*i).first == 1)
			{
				// Move Diagonally Left
				xLevel -= 1;
				yLevel += 1;
				safetyValue +=  world->getLevel().getPoint(xLevel, yLevel).getDifficulty();
			}
			
			if((*i).first == 2)
			{
				// Move vertically downwards
				yLevel += 1;
				safetyValue +=  world->getLevel().getPoint(xLevel, yLevel).getDifficulty();
			}

			if((*i).first == 3)
			{
				// Move Diagonally Right
				xLevel += 1;
				yLevel += 1;
				safetyValue +=  world->getLevel().getPoint(xLevel, yLevel).getDifficulty();
			}
		}
	}
	else
		{
			// X - Monotone Path
			for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
			{
				if((*i).first == 0)
				{
					// Save Previous xlevel
					int yPrevLevel = yLevel;

					// Move Vertically by (second) distance
					yLevel += (*i).second;

					for(int i = yPrevLevel; i <= yLevel; i++)
						safetyValue +=  world->getLevel().getPoint(xLevel, i).getDifficulty();
				}
				if((*i).first == 1)
				{
					// Move Diagonally UP
					xLevel += 1;
					yLevel -= 1;
					safetyValue +=  world->getLevel().getPoint(xLevel, yLevel).getDifficulty();
				}
			
				if((*i).first == 2)
				{
					// Move Horizontally Forward
					xLevel += 1;
					safetyValue +=  world->getLevel().getPoint(xLevel, yLevel).getDifficulty();
				}

				if((*i).first == 3)
				{
					// Move Diagonally Down
					xLevel += 1;
					yLevel += 1;
					safetyValue +=  world->getLevel().getPoint(xLevel, yLevel).getDifficulty();
				}
			}
		}

	function_value[1] = (double)((pathLength + 1)*(pathLength + 1) - safetyValue);
}

void Chromosome::repairOutofBounds()
{
	// Repair paths that go Outside The Level, wherever they go out of the level: straight line path to the goal
	// Make sure decode is called before calling this
	// decode();
	// xLevel and yLevel to maintain actual path in the level
	int xLevel = 0, yLevel = 0;

	if(monotone)
	{
		// Y - Monotone path
		for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
		{
			if((*i).first == 0)
			{
				// Save Previous xlevel
				int xPrevLevel = xLevel;

				// Move Horziontally by (second) distance
				xLevel += (*i).second;

				for(int j = xPrevLevel; j <= xLevel; j++)
					if(j == STARTX_GOAL && yLevel == STARTY_GOAL)
						return;
					else
					{
						// only Hit LEVEL_MAX_X and MIN Boundary...horizontal Movement
						if( j > LEVEL_MAX_X)
						{
							// Straight Line path to the goal along Y -axis
							// Check
							// Cache the remaining Length adn erase al lthe remaining path codes
							size_t remLength = i - path.end();
							path.erase(i, path.end());

							// Append all vertically downward direction codes
							for(size_t i = 0; i != remLength; i++)
								path.push_back(make_pair(2, 1));
						}

						if( j < LEVEL_MIN_X)
						{
							// Straight Line path to the goal along Y -axis
							// Check
							// Cache the remaining Length
							size_t remLength = i - path.end();
							path.erase(i, path.end());

							// Append all horizontally forward direction codes
							for(size_t i = 0; i != LEVEL_MAX_X; i++)
								path.push_back(make_pair(0, 1));

							// Append all vertically downward direction codes
							for(size_t i = 0; i < (remLength - LEVEL_MAX_X); i++)
								path.push_back(make_pair(2, 1));
						}
					}
			}

			if((*i).first == 1)
			{
				// Move Diagonally Left
				xLevel -= 1;
				yLevel += 1;
			}
			
			if((*i).first == 2)
			{
				// Move vertically downwards
				yLevel += 1;
			}

			if((*i).first == 3)
			{
				// Move Diagonally Right
				xLevel += 1;
				yLevel += 1;
			}

			if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
				return;

			// Out of Bounds Check
			if((xLevel > LEVEL_MAX_X))
			{
				// Straight Line path to the goal along Y -axis
				// Check
				// Cache the remaining Length and erase all the remaining path codes
				size_t remLength = i - path.end();
				path.erase(i, path.end());

				// Append all vertically downward direction codes
				for(size_t i = 0; i != remLength; i++)
					path.push_back(make_pair(2, 1));
			}
			
			if(yLevel > LEVEL_MAX_Y)
			{
				// Straight Line path parallel to X-axis
				// Cache the remaining Length and erase all the remaining path codes
				size_t remLength = i - path.end();
				path.erase(i, path.end());

				// Append all horizontally forward direction codes
				for(size_t i = 0; i != remLength; i++)
					path.push_back(make_pair(0, 1));
			}
			
		}
	}
	else
		{
			// X - Monotone Path
			for(vector<pair<int, int> >::const_iterator i = path.begin(); i != path.end(); i++)
			{
				if((*i).first == 0)
				{
					// Save Previous xlevel
					int yPrevLevel = yLevel;

					// Move Vertically by (second) distance
					yLevel += (*i).second;

					for(int j = yPrevLevel; j <= yLevel; j++)
						if(xLevel == STARTX_GOAL && j == STARTY_GOAL)
							return;
					else
					{
						// only Hit LEVEL_MAX_Y and MIN Boundary...horizontal Movement
						if( j > LEVEL_MAX_Y)
						{
							// Straight Line path to the goal along X -axis
							// Check
							// Cache the remaining Length adn erase al lthe remaining path codes
							size_t remLength = i - path.end();
							path.erase(i, path.end());

							// Append all horizontally forward direction codes
							for(size_t i = 0; i != remLength; i++)
								path.push_back(make_pair(2, 1));
						}

						if( j < LEVEL_MIN_Y)
						{
							// Straight Line path to the goal along Y -axis
							// Check
							// Cache the remaining Length
							size_t remLength = i - path.end();
							path.erase(i, path.end());

							// Append all vertically downward direction codes
							for(size_t i = 0; i != LEVEL_MAX_Y; i++)
								path.push_back(make_pair(0, 1));

							// Append all vertically downward direction codes
							for(size_t i = 0; i < (remLength - LEVEL_MAX_Y); i++)
								path.push_back(make_pair(2, 1));
						}
					}
				}

				if((*i).first == 1)
				{
					// Move Diagonally UP
					xLevel += 1;
					yLevel -= 1;
			
				}
			
				if((*i).first == 2)
				{
					// Move Horizontally Forward
					xLevel += 1;
				}

				if((*i).first == 3)
				{
					// Move Diagonally Down
					xLevel += 1;
					yLevel += 1;
				}
			
				if(xLevel == STARTX_GOAL && yLevel == STARTY_GOAL)
					return;

				// Out of Bounds Check, after every move according to path
				if((xLevel > LEVEL_MAX_X))
				{
					// Straight Line path to the goal along Y -axis
					// Check
					// Cache the remaining Length and erase all the remaining path codes
					size_t remLength = i - path.end();
					path.erase(i, path.end());

					// Append all vertically downward direction codes
					for(size_t i = 0; i != remLength; i++)
						path.push_back(make_pair(0, 1));
				}
				
				if(yLevel > LEVEL_MAX_Y)
				{
					// Straight Line path parallel to X-axis
					// Cache the remaining Length and erase all the remaining path codes
					size_t remLength = i - path.end();
					path.erase(i, path.end());

					// Append all horizontally forward direction codes
					for(size_t i = 0; i != remLength; i++)
						path.push_back(make_pair(2, 1));
				}
			}
		}

	// Repair paths that do not end in destination cell, continue straight line path
	// Do we need to?
}

// Repair paths that have a Solid Obstacle: Don't Know How To
void Chromosome::repairSolidObstacles()
{

}

// DO NOT USE
bool Chromosome::isValid() const
{
	return (isOutOfBounds() && (noOfObstacle() == 0) && goesThruGoal());
}

void Chromosome::display() const
{
	for(vector<int>::const_iterator i = binary_rep.begin(); i != binary_rep.end(); i++)
		cout<<(*i);
}