#include<SFML/Graphics.hpp>
#include <iostream>
#ifndef AFFICHAGE_INFOS
#define AFFICHAGE_INFOS
#include "affichage_infos.h"
#endif

class TitleScreen
{
public:
	TitleScreen(sf::Texture &texture_background);
	bool inputKey();
	void setBackground(sf::Texture &texture_background);
	void afficheBackground(sf::RenderWindow &window, sf::Texture &sprite);
private:
	sf::Sprite background;
	Infos information;
	Affichage affichage;
};