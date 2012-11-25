#ifndef WORLD_H
#define WORLD_H

#include "_config.h"
#include "Point.h"
#include "Enemy.h"
#include "Level.h"
#include <vector>

using std::vector;

/* Our main game world management class */
class World
{
private:
	Level level;
	vector<Enemy> enemies;

public:
	void initWorld();
	void drawWorld();

};

#endif