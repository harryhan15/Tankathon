#ifndef PLAYER_H
#define PLAYER_H

#include<string>

class Player {
private:
	std::string name;
	int projected_pick;
	std::string position;
	std::string team;
public:
	Player();
	~Player();
	Player(Player& p);

	int getProjectedPick();

	std::string getName();
	std::string getTeam();
	std::string getPosition();

	void createPlayer(std::string n, int pp, std::string pos, std::string t);
};

#endif