#ifndef PLAYER_H
#define PLAYER_H
#include <string>

using namespace std;

class Player
{
public:
	Player();
	Player(string, int);
	void setReinforcements(int);
	int getPlayerID();
	string getName();

protected:
private:
	string name;
	int playerID;
	int reinforcements;
};

#endif


