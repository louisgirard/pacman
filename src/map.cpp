#include "map.h"

Map::Map(sf::Texture &texture_background, sf::Texture &texture_sprites, sf::RenderWindow &window){
	setBackground(texture_background, window);
	setMaze();
	setSprites(texture_sprites);
}

void Map::setBackground(sf::Texture &texture_background, sf::RenderWindow &window){
    maze.setTexture(texture_background);
    maze.setPosition(MAP_X,MAP_Y);
    maze.setTextureRect(sf::IntRect(0,0,MAP_WIDTH,MAP_HEIGHT));
}

void Map::displayBackground(sf::RenderWindow &window, sf::Texture &sprite){
	//display maze
	window.draw(maze);
	//display scores
	display.displayScore(information.getScore(), sprite, MAP_X + 50, MAP_Y - 14, window);
	display.displayHighScore(information.getHighScore(), sprite, MAP_X + 150, MAP_Y - 14, window, true);
	//display lives/items
	display.displayLives(information.getLife(), sprite, MAP_X + 10, MAP_Y + MAP_HEIGHT + 1, window);
	display.displayItems(information.getItems(), sprite, MAP_X + 200, MAP_Y + MAP_HEIGHT + 1, window);
	//display ready
	if(!started){
		window.draw(ready);
	}
	//display balls
	for(size_t i = 0; i < invincibleBalls.size(); i++){
		window.draw(invincibleBalls.at(i));
	}
	for(size_t i = 0; i < litteBalls.size(); i++){
		window.draw(litteBalls.at(i));
	}
	//display characters
	window.draw(pacman.sprite);
	for(int i = 0; i < ghosts.size(); i++){
		window.draw(ghosts.at(i).sprite);
	}
}

void Map::setSprites(sf::Texture &texture_sprites){
	pacman.setSprite(texture_sprites, PACMAN_MAZE_X, PACMAN_MAZE_Y);
	setSprite(ready, texture_sprites, READY_MAZE_X, READY_MAZE_Y, READY_X, READY_Y, READY_WIDTH, READY_HEIGHT);

	//ghosts
	for(int i = 0; i < GHOST_NUMBER; i++){
		Ghost ghost(i);
		ghost.setSprite(texture_sprites, MAZE_X + 1, MAZE_Y + 1);
		ghosts.push_back(ghost);
	}

	sf::Sprite sprite;
	int x,y,cellSize,offset;
	
	cellSize = MAZE_WIDTH / 27;
	offset = 3;
	//invincibleBalls
	for(int i = 0; i < INVINCIBLE_BALL_NUMBER; i++){
		x = (i % 2) * (cellSize * 25) + MAZE_X + offset;
		y = i / 2 * (cellSize * 20) + MAZE_Y + offset + cellSize * 2;
		setSprite(sprite, texture_sprites, x, y, INVINCIBLE_BALL_X, INVINCIBLE_BALL_Y, INVINCIBLE_BALL_SIZE, INVINCIBLE_BALL_SIZE);
		invincibleBalls.push_back(sprite);
	}

	//littleBalls
	bool intersect = false; //intersect with other sprites
	offset = 7;
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 27; j++){
			intersect = false;
			if(mazeInfo[i][j] == 0){
				//1 cell = 2 cells in mazeInfo, remove dupplicate
				if((i+1) != 30 && (j+1) != 27 && mazeInfo[i+1][j] == 0 && mazeInfo[i][j+1] == 0 && mazeInfo[i+1][j+1] == 0){
					x = j * cellSize + MAZE_X + offset;
					y = i * cellSize + MAZE_Y + offset;
					setSprite(sprite, texture_sprites, x, y, LITTLE_BALL_X, LITTLE_BALL_Y, LITTLE_BALL_SIZE, LITTLE_BALL_SIZE);
					//check if intersect
					for(size_t i = 0; i < invincibleBalls.size(); i++){
						if(sprite.getGlobalBounds().intersects(invincibleBalls.at(i).getGlobalBounds())){
							intersect = true;
						}
					}
					if(sprite.getGlobalBounds().intersects(pacman.sprite.getGlobalBounds())){
						intersect = true;
					}
					if(sprite.getGlobalBounds().intersects(ready.getGlobalBounds())){
						intersect = true;
					}
					if (!intersect){
						litteBalls.push_back(sprite);
					}
				}
			}
		}
	}
}

void Map::setSprite(sf::Sprite &sprite, sf::Texture &texture_sprites, int x, int y, int sprite_x, int sprite_y, int width, int height){
	sprite.setTexture(texture_sprites);
	sprite.setPosition(x,y);
	sprite.setTextureRect(sf::IntRect(sprite_x,sprite_y,width,height));

}

void Map::setMaze(){
	std::ifstream mazefile;
	std::string fileline;
	int line = 0, column = 0;

	mazefile.open("data/maze.txt");
	if (!mazefile) {
    	perror("open file maze");
	}
	while(std::getline(mazefile, fileline)){
		for(std::string::iterator it = fileline.begin(); it != fileline.end(); ++it) {
		    mazeInfo[line][column] = *it - 48; //ASCII code, digits start from 48
		    column++;
		}
		column = 0;
		line++;
	}
	mazefile.close();
}

void Map::run(sf::RenderWindow &window, sf::Clock &time){
	//death
	if(pacman.dying){
		pacman.sprite.setPosition(PACMAN_MAZE_X, PACMAN_MAZE_Y);
		if (time.getElapsedTime().asMilliseconds() >= 100){
			pacman.animationDeath();
			time.restart();
		}
		return;
	}
	//characters move
	if (time.getElapsedTime().asMilliseconds() >= 35){
		pacman.move(mazeInfo, MAZE_X, MAZE_Y, MAZE_WIDTH, MAZE_HEIGHT);
		for(int i = 0; i < ghosts.size(); i++){
			ghosts.at(i).move(mazeInfo, MAZE_X, MAZE_Y, MAZE_WIDTH, MAZE_HEIGHT);
		}
		time.restart();
	}
	//invincibleBalls
	for(size_t i = 0; i < invincibleBalls.size(); i++){
		if(pacman.sprite.getGlobalBounds().intersects(invincibleBalls.at(i).getGlobalBounds())){
			information.addScore(50);
			invincibleBalls.erase(invincibleBalls.begin() + i);
		}
	}
	//littleBalls
	for(size_t i = 0; i < litteBalls.size(); i++){
		if(pacman.sprite.getGlobalBounds().intersects(litteBalls.at(i).getGlobalBounds())){
			information.addScore(10);
			litteBalls.erase(litteBalls.begin() + i);
		}
	}
	//ghosts
	for(size_t i = 0; i < ghosts.size(); i++){
		if(pacman.sprite.getGlobalBounds().intersects(ghosts.at(i).sprite.getGlobalBounds())){
			if(pacman.invincible && !ghosts.at(i).invincible){
				//kill ghost
			}else{
				pacman.dying = true;
				//lose life
				if(information.getLife() == 0){
					//lose game
				}else{
					information.loseLife();
				}
			}
		}
	}
}

void Map::start(){
	started = true;
	pacman.stop = false;
	for(int i = 0; i < ghosts.size(); i++){
		ghosts.at(i).stop = false;
	}
}