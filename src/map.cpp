#include "map.h"

Map::Map(sf::Texture &texture_background, sf::Texture &texture_sprites, sf::RenderWindow &main_window):window{main_window},texture{texture_sprites},maze{texture_background}{
	setSprites();
}

void Map::displayBackground(){
	//display maze
	window.draw(maze.sprite);
	//display scores
	display.displayScore(information.getScore(), texture, MAP_X + 50, MAP_Y - 14, window);
	display.displayHighScore(information.getHighScore(), texture, MAP_X + 150, MAP_Y - 14, window, true);
	//display lives/items
	display.displayLives(information.getLife(), texture, MAP_X + 10, MAP_Y + MAP_HEIGHT + 1, window);
	display.displayItems(information.getItems(), texture, MAP_X + 200, MAP_Y + MAP_HEIGHT + 1, window);
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

void Map::setSprite(sf::Sprite &sprite, int x, int y, int sprite_x, int sprite_y, int width, int height){
	sprite.setTexture(texture);
	sprite.setPosition(x,y);
	sprite.setTextureRect(sf::IntRect(sprite_x,sprite_y,width,height));

}

void Map::setSprites(){
	pacman.setSprite(texture, PACMAN_MAZE_X, PACMAN_MAZE_Y);
	setSprite(ready, READY_MAZE_X, READY_MAZE_Y, READY_X, READY_Y, READY_WIDTH, READY_HEIGHT);

	//ghosts
	for(int i = 0; i < GHOST_NUMBER; i++){
		Ghost ghost(i);
		ghost.setSprite(texture, GHOST_MAZE_X + i * 26, GHOST_MAZE_Y);
		ghosts.push_back(ghost);
	}

	setInvincibleBalls();
	setLittleBalls();
}

void Map::setInvincibleBalls(){
	sf::Sprite sprite;
	int x,y;	
	int cellSize = MAZE_WIDTH / 27;
	int offset = 3;
	for(int i = 0; i < INVINCIBLE_BALL_NUMBER; i++){
		x = (i % 2) * (cellSize * 25) + MAZE_X + offset;
		y = i / 2 * (cellSize * 20) + MAZE_Y + offset + cellSize * 2;
		setSprite(sprite, x, y, INVINCIBLE_BALL_X, INVINCIBLE_BALL_Y, INVINCIBLE_BALL_SIZE, INVINCIBLE_BALL_SIZE);
		invincibleBalls.push_back(sprite);
	}
}

void Map::setLittleBalls(){
	sf::Sprite sprite;
	int x,y;	
	int cellSize = MAZE_WIDTH / 27;
	int offset = 7;
	bool intersect = false; //intersect with other sprites
	for(int i = 0; i < 30; i++){
		for(int j = 0; j < 27; j++){
			intersect = false;
			if(maze.info[i][j] == 0){
				//1 cell = 2 cells in mazeInfo, remove dupplicate
				if((i+1) != 30 && (j+1) != 27 && maze.info[i+1][j] == 0 && maze.info[i][j+1] == 0 && maze.info[i+1][j+1] == 0){
					x = j * cellSize + MAZE_X + offset;
					y = i * cellSize + MAZE_Y + offset;
					setSprite(sprite, x, y, LITTLE_BALL_X, LITTLE_BALL_Y, LITTLE_BALL_SIZE, LITTLE_BALL_SIZE);
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
					if(i == 13 && (j == 11 || j == 12 || j == 13 || j == 14)){
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

void Map::run(){
	std::srand(std::time(nullptr));
	if (!started){
		if(startTimer.getElapsedTime().asMilliseconds() >= 2000){
			start();
			startTimer.restart();
		}
		return;
	}
	//death
	if(pacman.dying){
		if (pacmanTimer.getElapsedTime().asMilliseconds() >= 100){
			if(pacman.animationDeath()){// animation end
				if(information.getLife() < 0){
					reset();
				}else{
					restart();
				}
			}
			pacmanTimer.restart();
		}
		return;
	}
	//characters move
	if (pacmanTimer.getElapsedTime().asMilliseconds() >= NORMAL_SPEED){
		pacman.move(maze.info, MAZE_X, MAZE_Y, MAZE_WIDTH, MAZE_HEIGHT);
		pacmanTimer.restart();
	}
	for(size_t i = 0; i < ghosts.size(); i++){
		if(ghosts.at(i).weak() || ghosts.at(i).endWeak()){
			if (ghosts.at(i).timer.getElapsedTime().asMilliseconds() >= (NORMAL_SPEED * 2)){
				Direction direction;
				int dir = rand() % 4 + 1;
				direction = static_cast<Direction>(dir);
				//std::cout << "direction = " << direction << std::endl;
				ghosts.at(i).next_direction = direction;
				ghosts.at(i).move(maze.info, MAZE_X, MAZE_Y, MAZE_WIDTH, MAZE_HEIGHT);

				ghosts.at(i).timer.restart();
			}
		}else if(ghosts.at(i).dead()){
			if (ghosts.at(i).timer.getElapsedTime().asMilliseconds() >= (NORMAL_SPEED * 2)){
				int ghost_x = ghosts.at(i).cellX(MAZE_X, MAZE_WIDTH);
				int ghost_y = ghosts.at(i).cellY(MAZE_Y, MAZE_HEIGHT);
				ghosts.at(i).next_direction = astar.shortestPathDirection(maze.graph, ghost_x, ghost_y, 12, 13);
				//if ghost arrived in ghosts cage
				if(ghosts.at(i).next_direction == Null){
					ghosts.at(i).setNormal();
				}
				ghosts.at(i).move(maze.info, MAZE_X, MAZE_Y, MAZE_WIDTH, MAZE_HEIGHT);
				
				ghosts.at(i).timer.restart();
			}
		}else{ //normal
			if (ghosts.at(i).timer.getElapsedTime().asMilliseconds() >= NORMAL_SPEED){
				int ghost_x = ghosts.at(i).cellX(MAZE_X, MAZE_WIDTH);
				int ghost_y = ghosts.at(i).cellY(MAZE_Y, MAZE_HEIGHT);
				int pacman_x = pacman.cellX(MAZE_X, MAZE_WIDTH);
				int pacman_y = pacman.cellY(MAZE_Y, MAZE_HEIGHT);
				ghosts.at(i).next_direction = astar.shortestPathDirection(maze.graph, ghost_x, ghost_y, pacman_x, pacman_y);
				ghosts.at(i).move(maze.info, MAZE_X, MAZE_Y, MAZE_WIDTH, MAZE_HEIGHT);

				ghosts.at(i).timer.restart();
			}
		}
	}
	//invincible
	for(int i = 0; i < ghosts.size(); i++){
		if(ghosts.at(i).weak()){
			if (invincibleTimer.getElapsedTime().asMilliseconds() >= 7000){
				ghosts.at(i).setEndWeak();
			}
		}else if(!ghosts.at(i).dead()){
			if (invincibleTimer.getElapsedTime().asMilliseconds() >= 10000){
				ghosts.at(i).setNormal();
			}
		}
	}
	//invincibleBalls
	for(size_t i = 0; i < invincibleBalls.size(); i++){
		if(pacman.sprite.getGlobalBounds().intersects(invincibleBalls.at(i).getGlobalBounds())){
			for(size_t i = 0; i < ghosts.size(); i++){
				if(!ghosts.at(i).dead()){
					ghosts.at(i).setWeak();
				}
			}
			ghostsEaten = 0;
			invincibleTimer.restart();
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
			//ghost invincible = already killed
			if(ghosts.at(i).weak() || ghosts.at(i).endWeak()){
				//kill ghost
				ghostsEaten++;
				information.addScore(100 * pow(2,ghostsEaten));
				ghosts.at(i).setDead();
			}else if(ghosts.at(i).normal()){
				pacman.dying = true;
				//lose life
				information.loseLife();
			}
		}
	}
	//check victory
	if(litteBalls.size() == 0 && invincibleBalls.size() == 0){
		restart();
		invincibleBalls.clear();
		litteBalls.clear();
		setInvincibleBalls();
		setLittleBalls();
	}
}

void Map::start(){
	started = true;
	pacman.stop = false;
	pacmanTimer.restart();
	for(int i = 0; i < ghosts.size(); i++){
		ghosts.at(i).stop = false;
		ghosts.at(i).timer.restart();
		ghosts.at(i).start_timer.restart();
	}
}

void Map::reset(){
	restart();
	information.clearScore();
	information.gainLife();
	information.gainLife();
	information.gainLife();
	invincibleBalls.clear();
	litteBalls.clear();
	setInvincibleBalls();
	setLittleBalls();
}

void Map::restart(){
	started = false;
	startTimer.restart();
	pacman.sprite.setPosition(PACMAN_MAZE_X, PACMAN_MAZE_Y);
	pacmanTimer.restart();
	for(int i = 0; i < ghosts.size(); i++){
		ghosts.at(i).direction = Down;
		ghosts.at(i).sprite.setPosition(GHOST_MAZE_X + i * 26, GHOST_MAZE_Y);
		ghosts.at(i).timer.restart();
		ghosts.at(i).start_timer.restart();
	}	
}