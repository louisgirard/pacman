#ifndef PACMAN
#define PACMAN

#include <SFML/Graphics.hpp>
#include <iostream>
#include "character.h"

#define PACMAN_SIZE 13
#define PACMAN_X 43
#define PACMAN_Y 3
#define PACMAN_SPACE 7 //space between pacman sprites in sprite "pacman-sprites"

#define DEATH_X 2 //position of pacman death
#define DEATH_Y 221

class SpritePacman : public Character
{
public:
	SpritePacman();

	void input();
	void move(int maze[30][27], int x, int y, int width, int height);
	void animationMove(Direction direction);
	void animationDeath();

	int cellAnimationDeath;
	bool endAnimationDeath;
	bool invincible;
	Direction keyInput; //hold last input key to turn pacman according to it
};
#endif
