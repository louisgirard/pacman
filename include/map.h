#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include "display_information.h"
#include "sprite_pacman.h"
#include "information.h"

#define MAP_X 40
#define MAP_Y 31
#define MAP_WIDTH 224
#define MAP_HEIGHT 248

#define MAZE_X (MAP_X + 4)
#define MAZE_Y (MAP_Y + 4)
#define MAZE_WIDTH (MAP_WIDTH - 8)
#define MAZE_HEIGHT (MAP_HEIGHT - 8)

#define PACMANSTART_X (MAZE_X + (MAZE_WIDTH - PACMAN_SIZE) / 2)
#define PACMANSTART_Y 212

class Map
{
public:
	Information information;

	Map(sf::Texture &texture_background, sf::Texture &texture_sprites, sf::RenderWindow &window);

	void setBackground(sf::Texture &texture_background, sf::RenderWindow &window);
	void displayBackground(sf::RenderWindow &window, sf::Texture &sprite);

	void setMaze();

	void run(sf::RenderWindow &window, sf::Clock &time);
private:
	sf::Sprite maze;
	sf::RectangleShape background; //black bg
	Display display;
	//hold passable/not passable cells
	//0: passable, 1: not passable, 2: ghost cage, 3: ghost cage exit, 4: maze exit
	int mazeInfo[30][27];

	SpritePacman pacman;

};
#endif
