#include "sprite_pacman.h"

SpritePacman::SpritePacman():keyInput{Null},invincible{false},stop{false},direction{Left},poseAnimation{0},
poseAnimationMort{0},finAnimationMort{false}{
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

void SpritePacman::deplacement(int maze[30][27], int x, int y, int width, int height){
	Direction directionpassive = direction;
	int collision;
	input();
	if(!stop){
		if (keyInput != Null){
			//si il peut changer de direction alors il le fait
			direction = keyInput;
			collision = checkCollisions(maze,x,y,width,height);
			if (collision == 0){ //si on n'obtient pas de collision en changeant de direction
				keyInput = Null;
			}else{
				direction = directionpassive;
			}
		}
		collision = checkCollisions(maze,x,y,width,height);
		//continue tout seul dans la meme direction si pas de collision
		if (collision == 0){
			animationDeplacement(direction);
			if (direction == Up){
				sprite.move(0, -SPEED);
			}else if (direction == Down){
				sprite.move(0, SPEED);
			}else if (direction == Left){
				sprite.move(-SPEED, 0);
			}else if (direction == Right){
				sprite.move(SPEED, 0);
			}
		}
	}
}

int SpritePacman::checkCollisions(int maze[30][27], int x, int y, int width, int height){
	int xPacman, yPacman, caseSize; //en pixels
	int distanceMurFrontal, distanceMurLateral1, distanceMurLateral2;
	//les deux / trois cases adjacentes à pacman dans le labyrinthe, en coordonnées x et y
	sf::Vector2i case1;
	sf::Vector2i case2;
	sf::Vector2i case3;
	bool besoinCase3 = false;

	//largeur et hauteur d'une case en pixels
	caseSize = width / 27;//	caseSize = height / 30;

	//x et y de Pacman dans le referentiel du labyrinthe
	xPacman = sprite.getPosition().x - x;
	yPacman = sprite.getPosition().y - y;

	if (direction == Up){ //on ne s'intéresse qu'aux 2 cases du haut
		case1.x = xPacman /caseSize;
		case1.y = yPacman /caseSize - 1;
		case2.x = (xPacman + PACMAN_SIZE) /caseSize;
		case2.y = case1.y;
	}else if (direction == Down){ //on ne s'intéresse qu'aux 2 cases du bas
		case1.x = xPacman /caseSize;
		case1.y = (yPacman + PACMAN_SIZE) /caseSize + 1;
		case2.x = (xPacman + PACMAN_SIZE) /caseSize;
		case2.y = case1.y;
	}else if (direction == Left){
		case1.x = xPacman /caseSize - 1;
		case1.y = yPacman /caseSize;
		case2.x = case1.x;
		case2.y = (yPacman + PACMAN_SIZE) /caseSize;
	}else if (direction == Right){
		case1.x = (xPacman + PACMAN_SIZE) /caseSize + 1;
		case1.y = yPacman /caseSize;
		case2.x = case1.x;
		case2.y = (yPacman + PACMAN_SIZE) /caseSize;
	}

	//s'il y a une case entre les deux alors il faut la regarder
	if ((case2.x - case1.x) == 2){
		case3.x = case1.x + 1;
		case3.y = case1.y;
		besoinCase3 = true;
	}else if ((case2.y - case1.y) == 2){
		case3.x = case1.x;
		case3.y = case1.y + 1;
		besoinCase3 = true;		
	}

	//si on est devant des cases non passables ou au bord du labyrinthe
	if ((maze[case1.y][case1.x] != 0) || (maze[case2.y][case2.x] != 0) || ((maze[case3.y][case3.x] != 0) && besoinCase3)
		|| (case1.x < 0) || (case1.y < 0) || (case1.x > 26) || (case1.y > 29)){
		if (direction == Up){
			distanceMurFrontal = yPacman - case1.y * caseSize - caseSize;
		}else if (direction == Down){
			distanceMurFrontal = case1.y * caseSize - yPacman - PACMAN_SIZE;
		}else if (direction == Left){
			distanceMurFrontal = xPacman - case1.x * caseSize - caseSize;
		}else if (direction == Right){
			distanceMurFrontal = case1.x * caseSize - xPacman - PACMAN_SIZE;
		}
		//si on est en dessous ou egal a la marge de collision avec un mur alors il y a une collision
		if ((distanceMurFrontal <= MARGE_COLLISION_MAX) && 
			(distanceMurFrontal >= MARGE_COLLISION_MIN)){
			return 1;
		}else{
			return 0;
		}
	}else{
		//si on peut passer il faut qu'on soit au milieu de la case
		if ((direction == Up) || (direction == Down)){
			distanceMurLateral1 = xPacman - case1.x * caseSize;
			distanceMurLateral2 = case2.x * caseSize + caseSize - xPacman - PACMAN_SIZE;
		}else if((direction == Left) || direction == Right){
			distanceMurLateral1 = yPacman - case1.y * caseSize;
			distanceMurLateral2 = case2.y * caseSize + caseSize - yPacman - PACMAN_SIZE;
		}
		if((distanceMurLateral1 >= MARGE_COLLISION_MIN) &&
			(distanceMurLateral2 >= MARGE_COLLISION_MIN)){
			return 0;
		}else{
			return 1;
		}
	}
}

void SpritePacman::animationDeplacement(Direction direction){
	if (poseAnimation == 0){ //bouche fermée
		sprite.setTextureRect(sf::IntRect(PACMAN_X,PACMAN_Y,PACMAN_SIZE,PACMAN_SIZE));
	}else if((poseAnimation == 1) || (poseAnimation == 3)){
		sprite.setTextureRect(sf::IntRect(PACMAN_X - 2 * (PACMAN_SIZE + PACMAN_SPACE),PACMAN_Y + direction * (PACMAN_SIZE + PACMAN_SPACE),
			PACMAN_SIZE,PACMAN_SIZE));
	}else{
		sprite.setTextureRect(sf::IntRect(PACMAN_X - (PACMAN_SIZE + PACMAN_SPACE),PACMAN_Y + direction * (PACMAN_SIZE + PACMAN_SPACE),
			PACMAN_SIZE,PACMAN_SIZE));
	}
	poseAnimation = (poseAnimation + 1) % 4;
}

void SpritePacman::animationMort(){
	if(poseAnimationMort == 0){
		sprite.setPosition(sprite.getPosition().x - 1, sprite.getPosition().y);
	}
	sprite.setTextureRect(sf::IntRect(MORT_X + 20 * poseAnimationMort,MORT_Y,15,PACMAN_SIZE + 4));
	poseAnimationMort = (poseAnimationMort + 1) % 12;
	finAnimationMort = !poseAnimationMort;
}
