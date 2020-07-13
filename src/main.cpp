#include<SFML/Graphics.hpp>
#include <iostream>
#include "title_screen.h"
#include "map.h"

void load_texture(sf::Texture &texture, std::string texture_name);

int main(int argc, char const *argv[])
{
	/*Textures*/
	//Pour la performance il vaut mieux avoir le moins de textures possibles
	sf::Texture background;
	sf::Texture maze;
	sf::Texture sprites;
	load_texture(background, "images/title.jpg");
	load_texture(maze, "images/maze.png");
	load_texture(sprites, "images/pacman_sprites.png");

	/*Window*/
	sf::RenderWindow window;
	window.create(sf::VideoMode(303,295), "Pacman");
    
	/*Background title*/
	TitleScreen title(background);
	bool on_title = true; //au debut on est sur l'ecran titre

	/*Map*/
	Map map(maze, sprites, window);

	/*Clock*/
	sf::Clock time;

    /*Window*/
	while(window.isOpen()){
		/*Pour fermer la fenetre si on appuie sur la croix rouge*/
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				map.information.writeHighScore();
    			window.close();
    		}
		}
		window.clear();

		/*Title screen*/
		if (on_title){
			//dessine le fond d'ecran titre
			title.afficheBackground(window, sprites);
			if(title.inputKey()){ //si on a appuye sur la touche pour sortir de l'ecran titre
				on_title = false;
			}
		}else{
			/*On Map*/
			map.afficheBackground(window, sprites);
			map.run(window, time);
		}

		window.display();
		
	}
	return EXIT_SUCCESS;
}

void load_texture(sf::Texture &texture, std::string texture_name){
	if(!texture.loadFromFile(texture_name)){
        perror("erreur chargement texture numbers");
    }
}
