#include <SFML/Graphics.hpp>
#include <iostream>

#define SPEED 2 //vitesse de pacman

#define PACMAN_SIZE 13
#define PACMAN_X 43
#define PACMAN_Y 3
#define PACMAN_SPACE 7 //ecart entre les sprites de pacman sur l'image pacman-sprites

#define MORT_X 2 //emplacement de l'animation de mort de pacman
#define MORT_Y 221

#define MARGE_COLLISION_MAX 2 //marge entre pacman et un mur avant de rentrer en collision
#define MARGE_COLLISION_MIN 1

enum Direction{Left,Right,Up,Down,Null};

class SpritePacman
{
public:
	SpritePacman();
	void setSprite(sf::Texture &texture, int x, int y);

	void input();
	void deplacement(int maze[30][27], int x, int y, int width, int height);
	int checkCollisions(int maze[30][27], int x, int y, int width, int height); //0: no collisions, 1: collision, 2: no collision/edge of maze
	void animationDeplacement(Direction direction);
	void animationMort(); //renvoie true si l'animation est terminée

	sf::Sprite sprite;
	int poseAnimation; //0 : fermé, 1 : bouche peu ouverte, 2 : bouche grande ouverte, 3: bouche peu ouverte
	int poseAnimationMort;
	bool finAnimationMort;
	bool invincible;
	bool stop;
	Direction direction;
	Direction keyInput; //enregistre la dernière touche appuyée pour tourner pacman en conséquence
};
