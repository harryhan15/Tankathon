#include <fstream>
#include <iostream>
#include <time.h>   
#include <stdlib.h>
#include "generate.h"
#include "player.h"

Generate::Generate() {}

Generate::~Generate() {}

void Generate::run() {
	lottery.run();
	generatePlayer();

	int count = 0;

	do {
		srand(time(NULL));
		number.run();
		int* ln = number.getLotteryNumber();

		for (int i = 0; i < MAX_BALL; i++) {
			if (ln[0] == lottery.lotteryNum[i].num1 && ln[1] == lottery.lotteryNum[i].num2 &&
				ln[2] == lottery.lotteryNum[i].num3 && ln[3] == lottery.lotteryNum[i].num4) {

				if (lottery.getPick(lottery.lotteryNum[i].team) == 0) {
					count++;
					lottery.setPick(lottery.lotteryNum[i].team, count);
				}
			}
		}

	} while (count < 3);

	lottery.fillRemainingTeams();
	lottery.linkPlayerAndTeams(player);
}

void Generate::reset() {
	lottery.resetPick();
}

void Generate::initializeSim() {
	lottery.run();
	generatePlayer();
}

void Generate::runSim() {
	reset();

	int count = 0;

	do {
		srand(time(NULL));
		number.run();
		int* ln = number.getLotteryNumber();

		for (int i = 0; i < MAX_BALL; i++) {
			if (ln[0] == lottery.lotteryNum[i].num1 && ln[1] == lottery.lotteryNum[i].num2 &&
				ln[2] == lottery.lotteryNum[i].num3 && ln[3] == lottery.lotteryNum[i].num4) {

				if (lottery.getPick(lottery.lotteryNum[i].team) == 0) {
					count++;
					lottery.setPick(lottery.lotteryNum[i].team, count);
				}
			}
		}

	} while (count < 3);
}

void Generate::generatePlayer() {
	std::ifstream myFile("players.txt");

	std::string str;
	std::string NAME[TOTAL_TEAMS];
	std::string PROJ[TOTAL_TEAMS];
	std::string POS[TOTAL_TEAMS];
	std::string TEAM[TOTAL_TEAMS];

	int i = 0;
	int p;

	while (std::getline(myFile, str)) {
		p = 0;

		for (int j = 0; j < str.length(); j++) {
			if (p == 0) {
				if (str.at(j) == ',') {
					p++;
				}
				else {
					NAME[i] += str.at(j);
				}
			}
			else if (p == 1) {
				if (str.at(j) == ',') {
					p++;
				}
				else {
					PROJ[i] += str.at(j);
				}
			}
			else if (p == 2) {
				if (str.at(j) == ',') {
					p++;
				}
				else {
					POS[i] += str.at(j);
				}
			}
			else if (p == 3) {
				if (str.at(j) == ',') {
					p++;
				}
				else {
					TEAM[i] += str.at(j);
				}
			}
			else {
				break;
			}
		}


		player[i].createPlayer(NAME[i], atof(PROJ[i].c_str()), POS[i], TEAM[i]);
		i++;
	}
}

void Generate::count() {
	lottery.count();
}

void Generate::display() {
	lottery.display();
}

void Generate::displaySim() {
	lottery.displaySim();
}

void Generate::resetSim() {
	lottery.resetSim();
}