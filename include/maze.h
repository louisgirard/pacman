#ifndef MAZE
#define MAZE

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "astar.h"

#define MAP_X 40
#define MAP_Y 31
#define MAP_WIDTH 224
#define MAP_HEIGHT 248

class Maze{
public:
	Maze(sf::Texture &texture);

	sf::Sprite sprite;
	//hold passable/not passable cells
	//0: passable, 1: not passable, 2: ghost cage, 3: ghost cage exit, 4: maze exit
	int info[30][27];
	std::vector<std::vector<Node>> graph;

private:
	void setMaze();

};

#endif