/*
 * @Purpose: Home of the main() function
 * 
 */
#include "_config.h"
#include "World.h"
#include <iostream>
#include <conio.h>

int main()
{
	World* world;
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
	return 0;
}