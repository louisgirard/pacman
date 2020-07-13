#ifndef INFORMATION
#define INFORMATION

#include <list>
#include<fstream>
enum Items {cherry,strawberry,orange,apple,melon,flagship,bell,key};

class Information
{
public:
	Information();
	//lives
	void gainLife();
	void loseLife();
	int getLife();
	//score
	void addScore(int sc);
	int getScore();
	//high score
	void readHighScore();
	void writeHighScore();
	void addHighScore(int sc);
	int getHighScore();
	//items
	std::list<Items> getItems();
	void addItem(Items item);

private:
	int lives;
	std::list<Items> items;
	int score;
	int highScore;
	std::string fileScore;
};
#endif
