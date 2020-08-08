#include "ghost.h"

Ghost::Ghost(int ghost_id):Character(GHOST_X + ghost_id * 2 * (GHOST_SIZE + GHOST_SPACE),GHOST_Y,GHOST_SIZE,GHOST_SPACE){
	state = 0;
	id = ghost_id;
	direction = Down;
	next_direction = Null;
}

void Ghost::move(int maze[30][27], int maze_x, int maze_y, int maze_width, int maze_height){
	if(start_timer.getElapsedTime().asSeconds() < START_DELAY * id){
		return;
	}
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
			std::cout << "teleport ghost" << std::endl;
			//end of maze, teleport ghost
			if (direction == Left){
				sprite.move(maze_width - GHOST_SIZE - 11, 0);
			}else{
				sprite.move(GHOST_SIZE - maze_width + 11, 0);
			}
		}else{
			//collision
			//random direction when weak
			if(weak() || endWeak()){				
				Direction new_direction;
				do{
					do{
						int dir = rand() % 4;
						new_direction = static_cast<Direction>(dir);					
					}while((new_direction == Left && direction == Right) || (new_direction == Right && direction == Left) ||
						(new_direction == Up && direction == Down) || (new_direction == Down && direction == Up));
					oldDirection = direction;
					direction = new_direction;
					collision = checkMazeCollisions(maze,maze_x,maze_y,maze_width,maze_height);
					direction = oldDirection;
				}while(collision == 1);
				next_direction = new_direction;
			}
		}
	}
}

void Ghost::animationMove(Direction direction){
	//normal pose
	if(normal()){
		sprite.setTextureRect(sf::IntRect(GHOST_X + id * 2 * (GHOST_SIZE + GHOST_SPACE) + cellAnimation * (GHOST_SIZE + GHOST_SPACE),GHOST_Y + direction * (GHOST_SIZE + GHOST_SPACE),GHOST_SIZE,GHOST_SIZE));
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

bool Ghost::inCage(int maze_x, int maze_y){
	int ghost_x = sprite.getPosition().x - maze_x;
	int ghost_y = sprite.getPosition().y - maze_y;
	int cage_x = 84;
	int cage_y = 100;
	int cage_width = 48;
	int cage_height = 24;

	if(ghost_x >= cage_x && ghost_y >= cage_y && ghost_x <= (cage_x + cage_width) && ghost_y <= (cage_y + cage_height)){
		return true;
	}else{
		return false;
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