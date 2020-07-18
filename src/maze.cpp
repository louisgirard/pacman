#include "maze.h"

Maze::Maze(sf::Texture &texture){
    sprite.setTexture(texture);
    sprite.setPosition(MAP_X,MAP_Y);
    sprite.setTextureRect(sf::IntRect(0,0,MAP_WIDTH,MAP_HEIGHT));
    setMaze();
}

void Maze::setMaze(){
	std::ifstream mazeFile;
	std::string fileline;
	int line = 0, column = 0;

	mazeFile.open("data/maze.txt");
	if (!mazeFile) {
    	perror("open file maze");
	}
	while(std::getline(mazeFile, fileline)){
		graph.push_back({});
		for(std::string::iterator it = fileline.begin(); it != fileline.end(); ++it) {
		    info[line][column] = *it - 48; //ASCII code, digits start from 48

		    //graph
		    Node node;
		    node.x = column;
		    node.y = line;
		    node.value = *it - 48;
		    graph.at(line).push_back(node);

		    column++;
		}
		column = 0;
		line++;
	}
	mazeFile.close();
}