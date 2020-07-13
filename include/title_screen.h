#ifndef TITLE_SCREEN
#define TITLE_SCREEN

#include<SFML/Graphics.hpp>
#include <iostream>
#include "display_information.h"
#include "information.h"

class TitleScreen
{
public:
	TitleScreen(sf::Texture &texture_background);
	bool inputKey();
	void setBackground(sf::Texture &texture_background);
	void displayBackground(sf::RenderWindow &window, sf::Texture &sprite);
private:
	sf::Sprite background;
	Information information;
	Display display;
};
#endif
