#include "pacman.h"

Pacman::Pacman():Character(PACMAN_X,PACMAN_Y,PACMAN_SIZE,PACMAN_SPACE),keyInput{Null},cellAnimationDeath{0},dying{false}{
	invincible = false;
}

void Pacman::input(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        keyInput = Up;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        keyInput = Down;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        keyInput = Left;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
       	keyInput = Right;
    }
}

void Pacman::move(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height){
	Direction oldDirection = direction;
	int collision;
	input();
	if(!stop){
		if (keyInput != Null){
			direction = keyInput;
			collision = checkMazeCollisions(maze,maze_x,maze_y,maze_width,maze_height);
			if (collision == 0){ //if no collision when changing direction
				keyInput = Null;
			}else{
				direction = oldDirection;
			}
		}
		collision = checkMazeCollisions(maze,maze_x,maze_y,maze_width,maze_height);
		//follow same direction if no collision
		if (collision == 0){
			animationMove(direction);
			if (direction == Up){
				sprite.move(0, -speed);
			}else if (direction == Down){
				sprite.move(0, speed);
			}else if (direction == Left){
				sprite.move(-speed, 0);
			}else if (direction == Right){
				sprite.move(speed, 0);
			}
		}else if(collision == 2){
			//end of maze, teleport pacman
			if (direction == Left){
				sprite.move(maze_width - PACMAN_SIZE,0);
			}else{
				sprite.move(PACMAN_SIZE - maze_width,0);
			}
		}
	}
}

void Pacman::animationMove(Direction direction){
	if (cellAnimation == 0){ //closed mouth
		sprite.setTextureRect(sf::IntRect(PACMAN_X,PACMAN_Y,PACMAN_SIZE,PACMAN_SIZE));
	}else if((cellAnimation == 1) || (cellAnimation == 3)){
		sprite.setTextureRect(sf::IntRect(PACMAN_X - 2 * (PACMAN_SIZE + PACMAN_SPACE),PACMAN_Y + direction * (PACMAN_SIZE + PACMAN_SPACE),
			PACMAN_SIZE,PACMAN_SIZE));
	}else{
		sprite.setTextureRect(sf::IntRect(PACMAN_X - (PACMAN_SIZE + PACMAN_SPACE),PACMAN_Y + direction * (PACMAN_SIZE + PACMAN_SPACE),
			PACMAN_SIZE,PACMAN_SIZE));
	}
	cellAnimation = (cellAnimation + 1) % 4;
}

void Pacman::animationDeath(){
	if(cellAnimationDeath == 0){
		sprite.setPosition(sprite.getPosition().x - 1, sprite.getPosition().y);
	}
	sprite.setTextureRect(sf::IntRect(DEATH_X + 20 * cellAnimationDeath, DEATH_Y, 15, PACMAN_SIZE + 4));
	cellAnimationDeath = (cellAnimationDeath + 1) % 12;
	if(cellAnimationDeath == 0){
		dying = false;
		direction = Null;
		sprite.setTextureRect(sf::IntRect(PACMAN_X,PACMAN_Y,PACMAN_SIZE,PACMAN_SIZE));
	}
}
