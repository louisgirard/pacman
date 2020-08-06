#ifndef GHOST
#define GHOST

#include <vector>
#include <iostream>
#include <list>
#include "character.h"

#define GHOST_X 3
#define GHOST_Y 83
#define GHOST_WEAK_X 3
#define GHOST_WEAK_Y 163
#define GHOST_END_WEAK_X 43
#define GHOST_DEAD_X 83
#define GHOST_SIZE 14
#define GHOST_SPACE 6 //space between ghost sprites in sprite "pacman-sprites"

#define START_DELAY 3

class Ghost : public Character
{
public:
	Ghost(int ghost_id); //id of ghost, 1 = red ghost, 2 = pink ghost, etc..
	sf::Clock timer;
	sf::Clock start_timer;

	void input();
	void move(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height);
	void animationMove(Direction direction);
	Direction next_direction;

	bool inCage(int maze_x, int maze_y);

	void setNormal();
	void setWeak();
	void setEndWeak();
	void setDead();

	bool normal();
	bool weak();
	bool endWeak();
	bool dead();

private:
	int state; //0 = normal, 1 = weak, 2 = end weak, 3 = dead
	int id;
};
#endif