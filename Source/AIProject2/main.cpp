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
	World world;
	world.initWorld();
	world.drawWorld();

	getch();
	return 0;
}