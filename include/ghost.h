#ifndef GHOST
#define GHOST

#include <vector>
#include <iostream>
#include "character.h"

#define GHOST_X 3
#define GHOST_Y 83
#define GHOST_SIZE 14
#define GHOST_SPACE 6 //space between ghost sprites in sprite "pacman-sprites"

class Ghost : public Character
{
public:
	Ghost(int ghost_id); //id of ghost, 1 = red ghost, 2 = pink ghost, etc..

	void input();
	void move(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height);
	void animationMove(Direction direction);

	int id;
	std::vector<Direction> pattern;
	int id_current_pattern;
};
#endif