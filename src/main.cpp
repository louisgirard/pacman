#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "title_screen.h"
#include "map.h"

void load_texture(sf::Texture &texture, std::string texture_name);

int main()
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

	/*Start Sound*/
	sf::Sound start_sound;
	sf::SoundBuffer start_buffer;
	start_buffer.loadFromFile("sounds/pacman_beginning.wav");

	std::srand(std::time(nullptr));
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
			title.displayBackground(window, sprites);
			if(title.inputKey()){ //si on a appuye sur la touche pour sortir de l'ecran titre
				on_title = false;
				map.startTimer.restart();
				start_sound.setBuffer(start_buffer);
				start_sound.play();
			}
		}else{
			map.displayBackground();
			/*On Map*/
			map.run();
		}

		window.display();
		
	}
	return EXIT_SUCCESS;
}

void load_texture(sf::Texture &texture, std::string texture_name){
	if(!texture.loadFromFile(texture_name)){
        perror("load textures");
    }
}
