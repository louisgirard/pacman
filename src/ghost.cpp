#include "ghost.h"

Ghost::Ghost(int ghost_id):Character(GHOST_X + ghost_id * 5 * GHOST_SIZE,GHOST_Y,GHOST_SIZE,GHOST_SPACE){
	invincible = true;
	id = ghost_id;
	direction = Down;
	if(id == 0){
		pattern.push_back(Down);
		pattern.push_back(Right);
		pattern.push_back(Up);
		pattern.push_back(Left);
	}
	id_current_pattern = 0;
}

void Ghost::move(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height){
	int collision;
	if(!stop){
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
				sprite.move(maze_width - GHOST_SIZE,0);
			}else{
				sprite.move(GHOST_SIZE - maze_width,0);
			}
		}else{
			//collision, change direction
			id_current_pattern  = (id_current_pattern + 1) % pattern.size();
			direction = pattern.at(id_current_pattern);
		}
	}
}

void Ghost::animationMove(Direction direction){
	if (cellAnimation == 0){
		sprite.setTextureRect(sf::IntRect(GHOST_X + id * 5 * GHOST_SIZE,GHOST_Y + direction * (GHOST_SIZE + GHOST_SPACE),GHOST_SIZE,GHOST_SIZE));
	}else{
		sprite.setTextureRect(sf::IntRect(GHOST_X + id * 5 * GHOST_SIZE + GHOST_SIZE + GHOST_SPACE,GHOST_Y + direction * (GHOST_SIZE + GHOST_SPACE),
			GHOST_SIZE,GHOST_SIZE));
	}
	cellAnimation = (cellAnimation + 1) % 2;
}