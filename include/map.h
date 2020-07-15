#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "display_information.h"
#include "pacman.h"
#include "ghost.h"
#include "information.h"

#define MAP_X 40
#define MAP_Y 31
#define MAP_WIDTH 224
#define MAP_HEIGHT 248

#define MAZE_X (MAP_X + 4)
#define MAZE_Y (MAP_Y + 4)
#define MAZE_WIDTH (MAP_WIDTH - 8)
#define MAZE_HEIGHT (MAP_HEIGHT - 8)

#define PACMAN_MAZE_X (MAZE_X + (MAZE_WIDTH - PACMAN_SIZE) / 2)
#define PACMAN_MAZE_Y 212

#define INVINCIBLE_BALL_X 1
#define INVINCIBLE_BALL_Y 181
#define INVINCIBLE_BALL_SIZE 10
#define INVINCIBLE_BALL_NUMBER 4

#define LITTLE_BALL_X 16
#define LITTLE_BALL_Y 184
#define LITTLE_BALL_SIZE 2

#define READY_X 62
#define READY_Y 15
#define READY_WIDTH 56
#define READY_HEIGHT 9
#define READY_MAZE_X (MAZE_X + (MAZE_WIDTH - READY_WIDTH) / 2)
#define READY_MAZE_Y 167

#define GHOST_NUMBER 1

class Map
{
public:
	Information information;

	Map(sf::Texture &texture_background, sf::Texture &texture_sprites, sf::RenderWindow &main_window);

	void displayBackground();
	void run();
	void start();
	bool started = false;
	
private:
	sf::RenderWindow &window;
	sf::Texture &texture;
	sf::Clock time;
	sf::Clock invincibleTimer;

	bool ghostsWeak;
	sf::Sprite maze;
	Display display;
	//hold passable/not passable cells
	//0: passable, 1: not passable, 2: ghost cage, 3: ghost cage exit, 4: maze exit
	int mazeInfo[30][27];

	Pacman pacman;
	std::vector<Ghost> ghosts;
	sf::Sprite ready;
	std::vector<sf::Sprite> litteBalls;
	std::vector<sf::Sprite> invincibleBalls;

	void setBackground(sf::Texture &texture_background);
	void setSprite(sf::Sprite &sprite, int x, int y, int sprite_x, int sprite_y, int width, int height);
	void setSprites();
	void setMaze();
	void setInvincibleBalls();
	void setLittleBalls();
	void reset();

};
#endif
