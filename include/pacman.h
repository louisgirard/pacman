#ifndef PACMAN
#define PACMAN

#include "character.h"

#define PACMAN_X 43
#define PACMAN_Y 3
#define PACMAN_SIZE 13
#define PACMAN_SPACE 7 //space between pacman sprites in sprite "pacman-sprites"

#define DEATH_X 2 //position of pacman death
#define DEATH_Y 221

class Pacman : public Character
{
public:
	Pacman();

	void input();
	void move(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height);
	void animationMove(Direction direction);
	void animationDeath();

	int cellAnimationDeath;
	bool dying;
	Direction keyInput; //hold last input key to turn pacman according to it
};
#endif
