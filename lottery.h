#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "team.h"
#include "player.h"
#include "constants.h"

class Lottery {
private:
	Team lotteryTeams[MAX_LOTTERY_TEAMS];
	Team playoffTeams[MAX_PLAYOFF_TEAMS];
public:
	Lottery();
	~Lottery();

	void run();

	void generateTeams();
	void generateLotteryNumbers();

	void assignTeams();
	void assign(Team &t, int odds, int &count);

	void setPick(std::string name, int pick);
	int getPick(std::string name);

	void fillRemainingTeams();

	void linkPlayerAndTeams(Player p[]);
	void count();

	void resetPick();

	void generateOutputFile();
	void display();
	void displaySim();
	void resetSim();

	struct lotteryNumber {
		int num1;
		int num2;
		int num3;
		int num4;
		std::string team;
		bool occupied;
	};

	lotteryNumber lotteryNum[1001];
};