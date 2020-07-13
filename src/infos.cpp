#include "../include/infos.h"

Infos::Infos():lives{2}, score{0}{
	fileScore = "data/score.txt";
	readHighScore();
	items.clear();
}
//lives
void Infos::gainLife(){
	lives++;
}
void Infos::loseLife(){
	if (lives != 0)
		lives--;
}
int Infos::getLife(){
	return lives;
}
//score
void Infos::addScore(int sc){
	score += sc;
}
int Infos::getScore(){
	return score;
}
//high score
void Infos::readHighScore(){
	//read high score from a file
	std::ifstream filescore;
	std::string line;
	filescore.open(fileScore);
	if (!filescore) {
    	perror("ouverture file score");
	}
	std::getline(filescore, line);
	filescore.close();
	highScore = std::stoi(line);
}
void Infos::writeHighScore(){
	//read high score from a file
	std::ofstream filescore;
	filescore.open(fileScore);
	if (!filescore) {
    	perror("ouverture file score");
	}
	filescore << highScore;
	filescore.close();
}
void Infos::addHighScore(int sc){
	highScore += sc;
}
int Infos::getHighScore(){
	return highScore;
}
//items
std::list<Items> Infos::getItems(){
	return items;
}
void Infos::addItem(Items item){
	items.push_front(item);
}
