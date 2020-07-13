#include "information.h"

Information::Information():lives{2}, score{0}{
	fileScore = "data/score.txt";
	readHighScore();
	items.clear();
}
//lives
void Information::gainLife(){
	lives++;
}
void Information::loseLife(){
	if (lives != 0)
		lives--;
}
int Information::getLife(){
	return lives;
}
//score
void Information::addScore(int sc){
	score += sc;
}
int Information::getScore(){
	return score;
}
//high score
void Information::readHighScore(){
	//read high score from a file
	std::ifstream filescore;
	std::string line;
	filescore.open(fileScore);
	if (!filescore) {
    	perror("open file score");
	}
	std::getline(filescore, line);
	filescore.close();
	highScore = std::stoi(line);
}
void Information::writeHighScore(){
	//read high score from a file
	std::ofstream filescore;
	filescore.open(fileScore);
	if (!filescore) {
    	perror("open file score");
	}
	filescore << highScore;
	filescore.close();
}
void Information::addHighScore(int sc){
	highScore += sc;
}
int Information::getHighScore(){
	return highScore;
}
//items
std::list<Items> Information::getItems(){
	return items;
}
void Information::addItem(Items item){
	items.push_front(item);
}
