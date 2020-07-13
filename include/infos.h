#include <list>
#include<fstream>
enum Items {cherry,strawberry,orange,apple,melon,flagship,bell,key};

class Infos
{
public:
	Infos();
	//vies
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
	//objets
	std::list<Items> getItems();
	void addItem(Items item);

private:
	int lives;
	std::list<Items> items;
	int score;
	int highScore;
	std::string fileScore;
};
