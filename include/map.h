#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include "display_information.h"
#include "pacman.h"
#include "ghost.h"
#include "information.h"
#include "maze.h"

#define MAZE_X (MAP_X + 4) //without edges
#define MAZE_Y (MAP_Y + 4)
#define MAZE_WIDTH (MAP_WIDTH - 8) //inside of maze
#define MAZE_HEIGHT (MAP_HEIGHT - 8)

#define PACMAN_MAZE_X (MAZE_X + (MAZE_WIDTH - PACMAN_SIZE) / 2)
#define PACMAN_MAZE_Y 212
#define GHOST_MAZE_X PACMAN_MAZE_X - 14
#define GHOST_MAZE_Y 138

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

#define GHOST_NUMBER 2

#define NORMAL_SPEED 30

class Map
{
public:
	Information information;

	Map(sf::Texture &texture_background, sf::Texture &texture_sprites, sf::RenderWindow &main_window);

	void displayBackground();
	void run();
	void start();
	bool started = false;
	sf::Clock startTimer;

	int start_timer_duration = 5000;
	
private:
	sf::Sound sound;
	sf::SoundBuffer sound_buffer;

	sf::RenderWindow &window;
	sf::Texture &texture;
	sf::Clock pacmanTimer;
	sf::Clock invincibleTimer;
	Astar astar;

	int ghostsEaten = 0;
	Display display;
	Maze maze;


	Pacman pacman;
	std::vector<Ghost> ghosts;
	sf::Sprite ready;
	std::vector<sf::Sprite> litteBalls;
	std::vector<sf::Sprite> invincibleBalls;
	
	void setSprite(sf::Sprite &sprite, int x, int y, int sprite_x, int sprite_y, int width, int height);
	void setSprites();
	void setInvincibleBalls();
	void setLittleBalls();
	void reset();
	void restart();

};
#endif
