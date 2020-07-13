#include "sprite_pacman.h"

SpritePacman::SpritePacman():keyInput{Null},invincible{false},stop{false},direction{Left},cellAnimation{0},
cellAnimationDeath{0},endAnimationDeath{false}{
}

void SpritePacman::setSprite(sf::Texture &texture, int x, int y){
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
    sprite.setTextureRect(sf::IntRect(PACMAN_X,PACMAN_Y,PACMAN_SIZE,PACMAN_SIZE));
}

void SpritePacman::input(){
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

void SpritePacman::move(int maze[30][27], int x, int y, int width, int height){
	Direction oldDirection = direction;
	int collision;
	input();
	if(!stop){
		if (keyInput != Null){
			direction = keyInput;
			collision = checkCollisions(maze,x,y,width,height);
			if (collision == 0){ //if no collision when changing direction
				keyInput = Null;
			}else{
				direction = oldDirection;
			}
		}
		collision = checkCollisions(maze,x,y,width,height);
		//follow same direction if no collision
		if (collision == 0){
			animationMove(direction);
			if (direction == Up){
				sprite.move(0, -SPEED);
			}else if (direction == Down){
				sprite.move(0, SPEED);
			}else if (direction == Left){
				sprite.move(-SPEED, 0);
			}else if (direction == Right){
				sprite.move(SPEED, 0);
			}
		}else if(collision == 2){
			//end of maze, teleport pacman
			if (direction == Left){
				sprite.move(width - PACMAN_SIZE,0);
			}else{
				sprite.move(PACMAN_SIZE - width,0);
			}
		}
	}
}

int SpritePacman::checkCollisions(int maze[30][27], int x, int y, int width, int height){
	int xPacman, yPacman, cellSize; //en pixels
	int distanceFrontalWall, distanceSideWall1, distanceSideWall2;
	//two or three cells adjacent to pacman int the maze, x and y location
	sf::Vector2i cell1;
	sf::Vector2i cell2;
	sf::Vector2i cell3;
	bool needCell3 = false;

	//width and height of cell in pixels
	cellSize = width / 27;//	cellSize = height / 30;

	//location of Pacman in the maze
	xPacman = sprite.getPosition().x - x;
	yPacman = sprite.getPosition().y - y;

	if (direction == Up){ //focus on up cells
		cell1.x = xPacman /cellSize;
		cell1.y = yPacman /cellSize - 1;
		cell2.x = (xPacman + PACMAN_SIZE) / cellSize;
		cell2.y = cell1.y;
	}else if (direction == Down){ //focus on down cells
		cell1.x = xPacman /cellSize;
		cell1.y = (yPacman + PACMAN_SIZE) /cellSize + 1;
		cell2.x = (xPacman + PACMAN_SIZE) /cellSize;
		cell2.y = cell1.y;
	}else if (direction == Left){
		cell1.x = xPacman /cellSize - 1;
		cell1.y = yPacman /cellSize;
		cell2.x = cell1.x;
		cell2.y = (yPacman + PACMAN_SIZE) /cellSize;
	}else if (direction == Right){
		cell1.x = (xPacman + PACMAN_SIZE) /cellSize + 1;
		cell1.y = yPacman /cellSize;
		cell2.x = cell1.x;
		cell2.y = (yPacman + PACMAN_SIZE) /cellSize;
	}

	//if cell between cell1 and 2 then need to consider it
	if ((cell2.x - cell1.x) == 2){
		cell3.x = cell1.x + 1;
		cell3.y = cell1.y;
		needCell3 = true;
	}else if ((cell2.y - cell1.y) == 2){
		cell3.x = cell1.x;
		cell3.y = cell1.y + 1;
		needCell3 = true;		
	}

	//si on est devant des cases non passables ou au bord du labyrinthe
	if ((maze[cell1.y][cell1.x] != 0) || (maze[cell2.y][cell2.x] != 0) || ((maze[cell3.y][cell3.x] != 0) && needCell3)
		|| (cell1.x < 0) || (cell1.y < 0) || (cell1.x > 26) || (cell1.y > 29)){
		if (direction == Up){
			distanceFrontalWall = yPacman - cell1.y * cellSize - cellSize;
		}else if (direction == Down){
			distanceFrontalWall = cell1.y * cellSize - yPacman - PACMAN_SIZE;
		}else if (direction == Left){
			distanceFrontalWall = xPacman - cell1.x * cellSize - cellSize;
		}else if (direction == Right){
			distanceFrontalWall = cell1.x * cellSize - xPacman - PACMAN_SIZE;
		}
		//si on est en dessous ou egal a la marge de collision avec un mur alors il y a une collision
		if ((distanceFrontalWall <= MARGIN_COLLISION_MAX) && 
			(distanceFrontalWall >= MARGIN_COLLISION_MIN)){
			if (maze[cell1.y][cell1.x] == 4 || maze[cell2.y][cell2.x] == 4){
				return 2; //end of maze
			}else{
				return 1; //collision
			}
		}else{
			return 0;
		}
	}else{
		//si on peut passer il faut qu'on soit au milieu de la case
		if ((direction == Up) || (direction == Down)){
			distanceSideWall1 = xPacman - cell1.x * cellSize;
			distanceSideWall2 = cell2.x * cellSize + cellSize - xPacman - PACMAN_SIZE;
		}else if((direction == Left) || direction == Right){
			distanceSideWall1 = yPacman - cell1.y * cellSize;
			distanceSideWall2 = cell2.y * cellSize + cellSize - yPacman - PACMAN_SIZE;
		}
		if((distanceSideWall1 >= MARGIN_COLLISION_MIN) &&
			(distanceSideWall2 >= MARGIN_COLLISION_MIN)){
			return 0;
		}else{
			return 1;
		}
	}
}

void SpritePacman::animationMove(Direction direction){
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

void SpritePacman::animationDeath(){
	if(cellAnimationDeath == 0){
		sprite.setPosition(sprite.getPosition().x - 1, sprite.getPosition().y);
	}
	sprite.setTextureRect(sf::IntRect(DEATH_X + 20 * cellAnimationDeath, DEATH_Y, 15, PACMAN_SIZE + 4));
	cellAnimationDeath = (cellAnimationDeath + 1) % 12;
	endAnimationDeath = !cellAnimationDeath;
}
