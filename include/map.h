#include <SFML/Graphics.hpp>
#ifndef AFFICHAGE_INFOS
#define AFFICHAGE_INFOS
#include "affichage_infos.h"
#endif
#include "sprite_pacman.h"

#define MAP_X 40
#define MAP_Y 31
#define MAP_WIDTH 224
#define MAP_HEIGHT 248

#define MAZE_X (MAP_X + 4)
#define MAZE_Y (MAP_Y + 4)
#define MAZE_WIDTH (MAP_WIDTH - 8)
#define MAZE_HEIGHT (MAP_HEIGHT - 8)

#define PACMANDEPART_X (MAZE_X + (MAZE_WIDTH - PACMAN_SIZE) / 2)
#define PACMANDEPART_Y 212

class Map
{
public:
	Infos information;

	Map(sf::Texture &texture_background, sf::Texture &texture_sprites, sf::RenderWindow &window);

	void setBackground(sf::Texture &texture_background, sf::RenderWindow &window);
	void afficheBackground(sf::RenderWindow &window, sf::Texture &sprite);

	void setMaze();

	void run(sf::RenderWindow &window, sf::Clock &time);
private:
	sf::Sprite maze;
	sf::RectangleShape background; //fond noir
	Affichage affichage;
	//contient les passabilités du labyrinthe, 30 lignes et 27 colonnes
	//0 : passable, 1 : non passable, 2 : bord de la cage des fantomes, 3 : sortie de la cage des fantomes, 4 : sorties du labyrinthe
	int mazeInfos[30][27];

	SpritePacman pacman;

};