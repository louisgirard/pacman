#include "affichage_infos.h"
#include <iostream>

Affichage::Affichage(){}

//Affichage des scores

void Affichage::afficheScore(int sc, sf::Texture &texture, int x, int y, sf::RenderWindow &window, bool txt){
	sf::Sprite number;
	int compteur;
	std::list<int> score;
	
	transformeNombre(sc, score);
	
	number.setTexture(texture);
	//affiche "score"
	if (txt){
	    number.setPosition(sf::Vector2f(x - 20,y - 10));
	    number.setTextureRect(sf::IntRect(HIGHSCORE_X + 40, HIGHSCORE_Y, HIGHSCORE_WIDTH - 40, HIGHSCORE_HEIGHT));
	    window.draw(number);
	}
    compteur = score.size() - 1;
    for(std::list<int>::iterator it = score.begin(); it != score.end(); ++it){
	    number.setPosition(sf::Vector2f(x - compteur * NUMBER_WIDTH,y));
	    number.setTextureRect(sf::IntRect(NUMBER_X + *it * NUMBER_WIDTH, NUMBER_Y, NUMBER_WIDTH, NUMBER_HEIGHT));
	    window.draw(number);
	    compteur--;
    }
}

void Affichage::afficheHighScore(int sc, sf::Texture &texture, int x, int y, sf::RenderWindow &window, bool txt){
	sf::Sprite number;
	int compteur;
	std::list<int> highScore;
	
	transformeNombre(sc, highScore);

	number.setTexture(texture);
	//affiche "high score"
	if (txt){
	    number.setPosition(sf::Vector2f(x - 60,y - 10));
	    number.setTextureRect(sf::IntRect(HIGHSCORE_X, HIGHSCORE_Y, HIGHSCORE_WIDTH, HIGHSCORE_HEIGHT));
	    window.draw(number);
	}
    //affiche le high score
    compteur = highScore.size() - 1;
    for(std::list<int>::iterator it = highScore.begin(); it != highScore.end(); ++it){
	    number.setPosition(sf::Vector2f(x - compteur * NUMBER_WIDTH,y));
	    number.setTextureRect(sf::IntRect(NUMBER_X + *it * NUMBER_WIDTH, NUMBER_Y, NUMBER_WIDTH, NUMBER_HEIGHT));
	    window.draw(number);
	    compteur--;
    }
}

void Affichage::transformeNombre(int sc, std::list<int> &nombre){
	int nb = nombreChiffresScore(sc);
	nombre.clear();
	for (int i = (nb-1); i >= 0; i--){
		nombre.push_front(sc % 10);    
		sc /= 10;
	}
}

int Affichage::nombreChiffresScore(int sc){
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

//Affichage des vies

void Affichage::afficheVies(int nbVies, sf::Texture &texture, int x, int y, sf::RenderWindow &window){
	sf::Sprite number;
	for(int i = 0; i < nbVies; i++){
	    number.setTexture(texture);
	    number.setPosition(sf::Vector2f(x + i * LIFE_WIDTH,y));
	    number.setTextureRect(sf::IntRect(LIFE_X, LIFE_Y, LIFE_WIDTH, LIFE_HEIGHT));
	    window.draw(number);		
	}
}

//Affichage des 8 derniers objets
void Affichage::afficheItems(std::list<Items> items, sf::Texture &texture, int x, int y, sf::RenderWindow &window){
	sf::Sprite number;
	int compteur;

    compteur = (items.size() > 8) ? 7 : items.size() - 2;
    for(std::list<Items>::iterator it = items.begin(); (it != items.end()) && (compteur >= 0); ++it){
	    number.setTexture(texture);
	    number.setPosition(sf::Vector2f(x - compteur * ITEMS_WIDTH,y));
	    number.setTextureRect(sf::IntRect(ITEMS_X + ITEMS_WIDTH * *it, ITEMS_Y, ITEMS_WIDTH, ITEMS_HEIGHT));
	    window.draw(number);
	    compteur--;
    }
}
