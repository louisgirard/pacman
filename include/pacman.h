#include <SFML/Graphics.hpp>
#include <iostream>

#define SPEED 2 //pacman speed

#define PACMAN_SIZE 13
#define PACMAN_X 43
#define PACMAN_Y 3
#define PACMAN_SPACE 7 //space between pacman sprites in sprite "pacman-sprites"

#define DEATH_X 2 //position of pacman death
#define DEATH_Y 221

#define MARGIN_COLLISION_MAX 2 //margin between pacman and a wall before collision
#define MARGIN_COLLISION_MIN 1

enum Direction{Left,Right,Up,Down,Null};

class SpritePacman
{
public:
	SpritePacman();
	void setSprite(sf::Texture &texture, int x, int y);

	void input();
	void move(int maze[30][27], int x, int y, int width, int height);
	int checkMazeCollisions(int maze[30][27], int x, int y, int width, int height); //0: no collisions, 1: collision, 2: no collision/edge of maze
	void animationMove(Direction direction);
	void animationDeath();

	sf::Sprite sprite;
	int cellAnimation; //0: mouth closed, 1: mouth open, 2: mouth wide open, 3: mouth open
	int cellAnimationDeath;
	bool endAnimationDeath;
	bool invincible;
	bool stop;
	Direction direction;
	Direction keyInput; //hold last input key to turn pacman according to it
};
