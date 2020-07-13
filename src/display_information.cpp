#include "display_information.h"

Display::Display(){}

//Display scores

void Display::displayScore(int sc, sf::Texture &texture, int x, int y, sf::RenderWindow &window, bool txt){
	sf::Sprite number;
	int counter;
	std::list<int> score;
	
	convertNumber(sc, score);
	
	number.setTexture(texture);
	//display score
	if (txt){
	    number.setPosition(sf::Vector2f(x - 20,y - 10));
	    number.setTextureRect(sf::IntRect(HIGHSCORE_X + 40, HIGHSCORE_Y, HIGHSCORE_WIDTH - 40, HIGHSCORE_HEIGHT));
	    window.draw(number);
	}
    counter = score.size() - 1;
    for(std::list<int>::iterator it = score.begin(); it != score.end(); ++it){
	    number.setPosition(sf::Vector2f(x - counter * NUMBER_WIDTH,y));
	    number.setTextureRect(sf::IntRect(NUMBER_X + *it * NUMBER_WIDTH, NUMBER_Y, NUMBER_WIDTH, NUMBER_HEIGHT));
	    window.draw(number);
	    counter--;
    }
}

void Display::displayHighScore(int sc, sf::Texture &texture, int x, int y, sf::RenderWindow &window, bool txt){
	sf::Sprite number;
	int counter;
	std::list<int> highScore;
	
	convertNumber(sc, highScore);

	number.setTexture(texture);
	//display "high score"
	if (txt){
	    number.setPosition(sf::Vector2f(x - 60,y - 10));
	    number.setTextureRect(sf::IntRect(HIGHSCORE_X, HIGHSCORE_Y, HIGHSCORE_WIDTH, HIGHSCORE_HEIGHT));
	    window.draw(number);
	}
    counter = highScore.size() - 1;
    for(std::list<int>::iterator it = highScore.begin(); it != highScore.end(); ++it){
	    number.setPosition(sf::Vector2f(x - counter * NUMBER_WIDTH,y));
	    number.setTextureRect(sf::IntRect(NUMBER_X + *it * NUMBER_WIDTH, NUMBER_Y, NUMBER_WIDTH, NUMBER_HEIGHT));
	    window.draw(number);
	    counter--;
    }
}

void Display::convertNumber(int sc, std::list<int> &nombre){
	int nb = countDigitsScore(sc);
	nombre.clear();
	for (int i = (nb-1); i >= 0; i--){
		nombre.push_front(sc % 10);    
		sc /= 10;
	}
}

int Display::countDigitsScore(int sc){
	if (sc < 10){
		return 1;
	}else if(sc < 100){
		return 2;
	}else if(sc < 1000){
		return 3;
	}else if(sc < 10000){
		return 4;
	}else if(sc < 100000){
		return 5;
	}else if(sc < 1000000){
		return 6;
	}else{
		return 7;
	}
}

//Display lives

void Display::displayLives(int nbLives, sf::Texture &texture, int x, int y, sf::RenderWindow &window){
	sf::Sprite number;
	for(int i = 0; i < nbLives; i++){
	    number.setTexture(texture);
	    number.setPosition(sf::Vector2f(x + i * LIFE_WIDTH,y));
	    number.setTextureRect(sf::IntRect(LIFE_X, LIFE_Y, LIFE_WIDTH, LIFE_HEIGHT));
	    window.draw(number);		
	}
}

//Display last 8 items
void Display::displayItems(std::list<Items> items, sf::Texture &texture, int x, int y, sf::RenderWindow &window){
	sf::Sprite number;
	int counter;

    counter = (items.size() > 8) ? 7 : items.size() - 2;
    for(std::list<Items>::iterator it = items.begin(); (it != items.end()) && (counter >= 0); ++it){
	    number.setTexture(texture);
	    number.setPosition(sf::Vector2f(x - counter * ITEMS_WIDTH,y));
	    number.setTextureRect(sf::IntRect(ITEMS_X + ITEMS_WIDTH * *it, ITEMS_Y, ITEMS_WIDTH, ITEMS_HEIGHT));
	    window.draw(number);
	    counter--;
    }
}
