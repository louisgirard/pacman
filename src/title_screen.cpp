#include "title_screen.h"

TitleScreen::TitleScreen(sf::Texture &texture_background){
	setBackground(texture_background);
}
void TitleScreen::setBackground(sf::Texture &texture_background){
    background.setTexture(texture_background);
    background.setPosition(0,0);
}
bool TitleScreen::inputKey(){
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
}
void TitleScreen::displayBackground(sf::RenderWindow &window, sf::Texture &sprite){
	window.draw(background);
	display.displayHighScore(information.getHighScore(), sprite, 160, 55, window);
}
