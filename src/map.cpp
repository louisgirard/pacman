#include "map.h"
#include <iostream>

Map::Map(sf::Texture &texture_background, sf::Texture &texture_sprites, sf::RenderWindow &window){
	setBackground(texture_background, window);
	setMaze();
	pacman.setSprite(texture_sprites, PACMANSTART_X, PACMANSTART_Y);
}

void Map::setBackground(sf::Texture &texture_background, sf::RenderWindow &window){
	background.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::Black);

    maze.setTexture(texture_background);
    maze.setPosition(MAP_X,MAP_Y);
    maze.setTextureRect(sf::IntRect(0,0,MAP_WIDTH,MAP_HEIGHT));
}
void Map::displayBackground(sf::RenderWindow &window, sf::Texture &sprite){
	//black bg
	window.draw(background);
	//display maze
	window.draw(maze);
	//display scores
	display.displayScore(information.getScore(), sprite, MAP_X + 50, MAP_Y - 14, window);
	display.displayHighScore(information.getHighScore(), sprite, MAP_X + 150, MAP_Y - 14, window, true);
	//display lives/items
	display.displayLives(information.getLife(), sprite, MAP_X + 10, MAP_Y + MAP_HEIGHT + 1, window);
	display.displayItems(information.getItems(), sprite, MAP_X + 200, MAP_Y + MAP_HEIGHT + 1, window);
}

void Map::setMaze(){
	std::ifstream mazefile;
	std::string fileline;
	int line = 0, column = 0;

	mazefile.open("data/maze.txt");
	if (!mazefile) {
    	perror("open file maze");
	}
	while(std::getline(mazefile, fileline)){
		for(std::string::iterator it = fileline.begin(); it != fileline.end(); ++it) {
		    mazeInfo[line][column] = *it - 48; //ASCII code, digits start from 48
		    column++;
		}
		column = 0;
		line++;
	}
	mazefile.close();
}

void Map::run(sf::RenderWindow &window, sf::Clock &time){
	window.draw(pacman.sprite);
	if (time.getElapsedTime().asMilliseconds() >= 30){
		pacman.move(mazeInfo, MAZE_X, MAZE_Y, MAZE_WIDTH, MAZE_HEIGHT);
		time.restart();
	}
	
	/*
	pacman.stop = true;
	if (!pacman.finAnimationMort){
		if (time.getElapsedTime().asMilliseconds() >= 100){
			pacman.animationMort();
			time.restart();
		}
	}*/
}
