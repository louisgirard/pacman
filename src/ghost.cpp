#include "ghost.h"

Ghost::Ghost(int ghost_id):Character(GHOST_X + ghost_id * 5 * GHOST_SIZE,GHOST_Y,GHOST_SIZE,GHOST_SPACE){
	state = 0;
	id = ghost_id;
	direction = Down;
	next_direction = Null;
}

void Ghost::move(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height){
	Direction oldDirection = direction;
	int collision;
	if(!stop){
		if (next_direction != Null){
			direction = next_direction;
			collision = checkMazeCollisions(maze,maze_x,maze_y,maze_width,maze_height);
			if (collision == 0 || collision == 3){ //if no collision when changing direction
				next_direction = Null;
			}else{
				direction = oldDirection;
			}
		}
		collision = checkMazeCollisions(maze,maze_x,maze_y,maze_width,maze_height);
		//follow same direction if no collision
		if (collision == 0 || collision == 3){
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
			//end of maze, teleport ghost
			if (direction == Left){
				sprite.move(maze_width - GHOST_SIZE - 11, 0);
			}else{
				sprite.move(GHOST_SIZE - maze_width + 11, 0);
			}
		}else{
			std::cout << "collision" << std::endl;
		}
	}
}

void Ghost::animationMove(Direction direction){
	//normal pose
	if(normal()){
		sprite.setTextureRect(sf::IntRect(GHOST_X + id * 5 * GHOST_SIZE + cellAnimation * (GHOST_SIZE + GHOST_SPACE),GHOST_Y + direction * (GHOST_SIZE + GHOST_SPACE),GHOST_SIZE,GHOST_SIZE));
		cellAnimation = (cellAnimation + 1) % 2;
	}else if(weak()){
		sprite.setTextureRect(sf::IntRect(GHOST_WEAK_X + (GHOST_SIZE + GHOST_SPACE) * cellAnimation, GHOST_WEAK_Y,GHOST_SIZE,GHOST_SIZE));
		cellAnimation = (cellAnimation + 1) % 2;
	}else if(endWeak()){
		if(cellAnimation > 1){
			sprite.setTextureRect(sf::IntRect(GHOST_WEAK_X + (GHOST_SIZE + GHOST_SPACE) * cellAnimation % 2, GHOST_WEAK_Y,GHOST_SIZE,GHOST_SIZE));
		}else{
			sprite.setTextureRect(sf::IntRect(GHOST_END_WEAK_X + (GHOST_SIZE + GHOST_SPACE) * cellAnimation, GHOST_WEAK_Y,GHOST_SIZE,GHOST_SIZE));
		}
		cellAnimation = (cellAnimation + 1) % 4;
	}else{//dead
		sprite.setTextureRect(sf::IntRect(GHOST_DEAD_X + (GHOST_SIZE + GHOST_SPACE) * direction, GHOST_WEAK_Y,GHOST_SIZE,GHOST_SIZE));
	}
}

void Ghost::setNormal(){
	state = 0;
	speed = 2;
}

void Ghost::setWeak(){
	state = 1;
	speed = 2;
}

void Ghost::setEndWeak(){
	state = 2;
}

void Ghost::setDead(){
	state = 3;
}

bool Ghost::normal(){
	return state == 0;
}

bool Ghost::weak(){
	return state == 1;
}

bool Ghost::endWeak(){
	return state == 2;
}

bool Ghost::dead(){
	return state == 3;
}