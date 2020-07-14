#include "character.h"

Character::Character(int x, int y, int size, int space):stop{true},direction{Down},cellAnimation{0},speed{2}{
	sprite_x = x;
	sprite_y = y;
	sprite_size = size;
	sprite_space = space;
}

void Character::setSprite(sf::Texture &texture, int x, int y){
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
    sprite.setTextureRect(sf::IntRect(sprite_x,sprite_y,sprite_size,sprite_size));
}

int Character::checkMazeCollisions(int maze[30][27], int x, int y, int width, int height){
	int x_character, y_character, cellSize; //en pixels
	int distanceFrontalWall, distanceSideWall1, distanceSideWall2;
	//two or three cells adjacent to character int the maze, x and y location
	sf::Vector2i cell1;
	sf::Vector2i cell2;
	sf::Vector2i cell3;
	bool needCell3 = false;

	//width and height of cell in pixels
	cellSize = width / 27;//	cellSize = height / 30;

	//location of character in the maze
	x_character = sprite.getPosition().x - x;
	y_character = sprite.getPosition().y - y;

	if (direction == Up){ //focus on up cells
		cell1.x = x_character /cellSize;
		cell1.y = y_character /cellSize - 1;
		cell2.x = (x_character + sprite_size) / cellSize;
		cell2.y = cell1.y;
	}else if (direction == Down){ //focus on down cells
		cell1.x = x_character /cellSize;
		cell1.y = (y_character + sprite_size) /cellSize + 1;
		cell2.x = (x_character + sprite_size) /cellSize;
		cell2.y = cell1.y;
	}else if (direction == Left){
		cell1.x = x_character /cellSize - 1;
		cell1.y = y_character /cellSize;
		cell2.x = cell1.x;
		cell2.y = (y_character + sprite_size) /cellSize;
	}else if (direction == Right){
		cell1.x = (x_character + sprite_size) /cellSize + 1;
		cell1.y = y_character /cellSize;
		cell2.x = cell1.x;
		cell2.y = (y_character + sprite_size) /cellSize;
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

	//if in front of not passable cells or edge of maze
	if ((maze[cell1.y][cell1.x] != 0) || (maze[cell2.y][cell2.x] != 0) || ((maze[cell3.y][cell3.x] != 0) && needCell3)
		|| (cell1.x < 0) || (cell1.y < 0) || (cell1.x > 26) || (cell1.y > 29)){
		if (direction == Up){
			distanceFrontalWall = y_character - cell1.y * cellSize - cellSize;
		}else if (direction == Down){
			distanceFrontalWall = cell1.y * cellSize - y_character - sprite_size;
		}else if (direction == Left){
			distanceFrontalWall = x_character - cell1.x * cellSize - cellSize;
		}else if (direction == Right){
			distanceFrontalWall = cell1.x * cellSize - x_character - sprite_size;
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
		//if it can pass, need to be in the middle of a cell
		if ((direction == Up) || (direction == Down)){
			distanceSideWall1 = x_character - cell1.x * cellSize;
			distanceSideWall2 = cell2.x * cellSize + cellSize - x_character - sprite_size;
		}else if((direction == Left) || direction == Right){
			distanceSideWall1 = y_character - cell1.y * cellSize;
			distanceSideWall2 = cell2.y * cellSize + cellSize - y_character - sprite_size;
		}
		if((distanceSideWall1 >= MARGIN_COLLISION_MIN) &&
			(distanceSideWall2 >= MARGIN_COLLISION_MIN)){
			return 0;
		}else{
			return 1;
		}
	}
}