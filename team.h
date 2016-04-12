#ifndef TEAM_H
#define TEAM_H

#include <string>
#include "player.h"

class Team {
private:
	double pick_odds;
	std::string name;
	std::string player;
	int overall;
	int pick;

	int first_pick;
	int second_pick;
	int third_pick;

	Player p;
public:
	Team();

	~Team();
	Team(Team& t);

	void createTeam(std::string name, double pick, int o);

	std::string getName();
	double getPickOdds();

	void setPick(int pick);
	int getPick();

	void setPlayer(Player p);
	int movement();

	void incrementFirstPick();
	void incrementSecondPick();
	void incrementThirdPick();
	void reset();

	void display();
	void displaySim();

	std::string nameToUpper(std::string name);
};

#endif