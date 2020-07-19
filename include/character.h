#ifndef CHARACTER
#define CHARACTER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define MARGIN_COLLISION_MAX 2 //margin between character and a wall before collision
#define MARGIN_COLLISION_MIN 1

#ifndef DIRECTION
#define DIRECTION
enum Direction{Left,Right,Up,Down,Null};
#endif

class Character{
public:
	Character(int x, int y, int size, int space);
	void setSprite(sf::Texture &texture, int x, int y);
	int checkMazeCollisions(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height); //0: no collisions, 1: collision, 2: no collision/edge of maze
	virtual void move(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height) = 0;
	virtual void animationMove(Direction direction) = 0;
	int cellX(int maze_x, int maze_width);
	int cellY(int maze_y, int maze_height);

	sf::Sprite sprite;
	bool stop;

protected:
	int cellAnimation;
	Direction direction;

	int speed;
	int sprite_x;
	int sprite_y;
	int sprite_size;
	int sprite_space;
};
#endif