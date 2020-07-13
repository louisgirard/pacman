#ifndef DISPLAY_INFORMATION
#define DISPLAY_INFORMATION

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "information.h"

#define NUMBER_WIDTH 10
#define NUMBER_HEIGHT 8
#define NUMBER_X 23 //x position of number in sprite
#define NUMBER_Y 181

#define HIGHSCORE_X 129
#define HIGHSCORE_Y 182
#define HIGHSCORE_WIDTH 80
#define HIGHSCORE_HEIGHT 11

#define LIFE_WIDTH 14
#define LIFE_HEIGHT 14
#define LIFE_X 42
#define LIFE_Y 22

#define ITEMS_WIDTH 14
#define ITEMS_HEIGHT 12
#define ITEMS_X 45
#define ITEMS_Y 63

class Display
{
public:
	Display();

	void displayScore(int sc, sf::Texture &texture, int x, int y, sf::RenderWindow &window, bool txt = true);
	void displayHighScore(int sc, sf::Texture &texture, int x, int y, sf::RenderWindow &window, bool txt = false);
	void convertNumber(int sc, std::list<int> &number); //convert number in list
	int countDigitsScore(int sc);

	void displayLives(int nbLives, sf::Texture &texture, int x, int y, sf::RenderWindow &window);

	void displayItems(std::list<Items> items, sf::Texture &texture, int x, int y, sf::RenderWindow &window);
};

#endif
