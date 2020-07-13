#include <SFML/Graphics.hpp>
#include "infos.h"
#include <list>

#define NUMBER_WIDTH 10 //largeur d'un chiffre
#define NUMBER_HEIGHT 8
#define NUMBER_X 23 //position x des nombres sur l'image pacman_sprites.png
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

class Affichage
{
public:
	Affichage();

	void afficheScore(int sc, sf::Texture &texture, int x, int y, sf::RenderWindow &window, bool txt = true);
	void afficheHighScore(int sc, sf::Texture &texture, int x, int y, sf::RenderWindow &window, bool txt = false);
	void transformeNombre(int sc, std::list<int> &nombre); //transforme un nombre en une liste de ses chiffres
	int nombreChiffresScore(int sc); //calcule le nombre de chiffres dans un nombre

	void afficheVies(int nbVies, sf::Texture &texture, int x, int y, sf::RenderWindow &window);

	void afficheItems(std::list<Items> items, sf::Texture &texture, int x, int y, sf::RenderWindow &window);
};
