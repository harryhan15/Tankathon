#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "lottery.h"

Lottery::Lottery() {
}

Lottery::~Lottery() {}

void Lottery::run() {
	srand(time(NULL));

	generateTeams();

	generateLotteryNumbers();
	assignTeams();

	generateOutputFile();
}

void Lottery::generateTeams() {
	std::ifstream myFile("teams.txt");

	std::string str;
	std::string STRING[TOTAL_TEAMS];
	double DOUBLE[TOTAL_TEAMS];

	int i = 0;
	int p = 0;
	while (std::getline(myFile, str)) {
		for (int j = 0; j < str.length(); j++) {
			if (str.at(j) == ',') {
				DOUBLE[i] = atof(str.substr(j + 2).c_str());
				break;
			}
			STRING[i] += str.at(j);
		}
		if (i < 14) {
			lotteryTeams[i].createTeam(STRING[i], DOUBLE[i], i + 1);
		}
		else {
			playoffTeams[p].createTeam(STRING[i], DOUBLE[i], i + 1);
			playoffTeams[p].setPick(i+1);
			p++;
		}
		i++;
	}
}

void Lottery::generateLotteryNumbers() {
	int first = 1;
	int second = 2;
	int third = 3;
	int fourth = 4;

	int i = 0;
	while (true) {
		lotteryNum[i].num1 = first;
		lotteryNum[i].num2 = second;
		lotteryNum[i].num3 = third;
		lotteryNum[i].num4 = fourth;
		lotteryNum[i].team = "";
		lotteryNum[i].occupied = false;

		fourth++;

		if (fourth > FOURTH_NUM_MAX) {
			third++;
			fourth = third + 1;

			if (third > THIRD_NUM_MAX) {
				second++;
				third = second + 1;
				fourth = third + 1;

				if (second > SECOND_NUM_MAX) {
					first++;
					second = first + 1;
					third = second + 1;
					fourth = third + 1;

					if (first > FIRST_NUM_MAX) {
						break;
					}
				}
			}
		}
		i++;
	}
}

void Lottery::assignTeams() {
	double odds = 0;
	int count;

	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		count = 0;
		odds = lotteryTeams[i].getPickOdds() * RANDOM_NUM;

		assign(lotteryTeams[i], odds, count);
	}
}

void Lottery::assign(Team &t, int odds, int &count) {
	int randomNum = rand() % RANDOM_NUM;

	if (!lotteryNum[randomNum].occupied) {
		lotteryNum[randomNum].team = t.getName();
		lotteryNum[randomNum].occupied = true;

		count++;
	}
	else {
		assign(t, odds, count);
	}

	if (count != odds) {
		assign(t, odds, count);
	}
}

void Lottery::setPick(std::string name, int pick) {
	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		if (name == lotteryTeams[i].getName()) {
			lotteryTeams[i].setPick(pick);
		}
	}
}

int Lottery::getPick(std::string name) {
	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		if (name == lotteryTeams[i].getName()) {
			return lotteryTeams[i].getPick();
		}
	}
}

void Lottery::fillRemainingTeams() {
	int p = AMOUNT;

	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		if (getPick(lotteryTeams[i].getName()) == 0) {
			setPick(lotteryTeams[i].getName(), p);
			p++;
		}
	}
}

void Lottery::linkPlayerAndTeams(Player p[]) {
	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		for (int j = 0; j < TOTAL_TEAMS; j++) {
			if (lotteryTeams[i].getPick() == p[j].getProjectedPick()) {
				lotteryTeams[i].setPlayer(p[j]);
			}
		}
	}

	for (int i = 0; i < MAX_PLAYOFF_TEAMS; i++) {
		for (int j = 0; j < TOTAL_TEAMS; j++) {
			if (playoffTeams[i].getPick() == p[j].getProjectedPick()) {
				playoffTeams[i].setPlayer(p[j]);
			}
		}
	}
}

void Lottery::count() {
	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		if (lotteryTeams[i].getPick() == 1) {
			lotteryTeams[i].incrementFirstPick();
		}
		else if (lotteryTeams[i].getPick() == 2) {
			lotteryTeams[i].incrementSecondPick();
		}
		else if (lotteryTeams[i].getPick() == 3) {
			lotteryTeams[i].incrementThirdPick();
		}
	}
}

void Lottery::resetPick() {
	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		lotteryTeams[i].setPick(0);
	}
}

void Lottery::generateOutputFile() {
	std::ofstream newFile;
	newFile.open("generated.txt");

	for (int i = 0; i < MAX_BALL; i++) {
		newFile << i + 1;
		newFile << ": ";
		newFile << lotteryNum[i].num1;
		newFile << " ";
		newFile << lotteryNum[i].num2;
		newFile << " ";
		newFile << lotteryNum[i].num3;
		newFile << " ";
		newFile << lotteryNum[i].num4;
		newFile << " ";
		newFile << lotteryNum[i].team;
		newFile << "\n";
	}

	newFile.close();
}

void Lottery::display() {

	std::cout << "Simulation Complete\n\n";
	Sleep(1000);
	std::cout << "|------------------------------------------------------------------------------------------------|\n";
	std::cout << "|" << std::setw(27) << std::left << "Pick" << "|";
	std::cout << std::setw(20) << std::left << "Player" << "|";
	std::cout << std::setw(10) << std::left << "Position" << "|";
	std::cout << std::setw(25) << std::left << "Team" << "|";
	std::cout << std::setw(10) << std::left << "Movement" << "|";
	std::cout << "\n";
	std::cout << "|------------------------------------------------------------------------------------------------|\n";
	for (int i = 1; i < MAX_LOTTERY_TEAMS + 1; i++) {
		for (int j = 0; j < MAX_LOTTERY_TEAMS; j++) {
			if (lotteryTeams[j].getPick() == i) {
				lotteryTeams[j].display();

				if (i < 4) {
					Sleep(1000);
				}
				
				if (i == 3) {
					std::cout << "|------------------------------------------------------------------------------------------------|\n";
				}
			}
		}
	}

	std::cout << "|------------------------------------------------------------------------------------------------|\n";
	Sleep(1000);

	for (int i = 0; i < MAX_PLAYOFF_TEAMS; i++) {
		playoffTeams[i].display();
	}

	std::cout << "|------------------------------------------------------------------------------------------------|\n";
}

void Lottery::displaySim() {
	std::cout << "|----------------------------------------------------------------------------------|\n";
	std::cout << "|" << std::setw(25) << std::left << "Team" << "|";
	std::cout << std::setw(18) << std::left << "First Overall" << "|";
	std::cout << std::setw(18) << std::left << "Second Overall" << "|";
	std::cout << std::setw(18) << std::left << "Third Overall" << "|";
	std::cout << "\n";
	std::cout << "|----------------------------------------------------------------------------------|\n";

	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		lotteryTeams[i].displaySim();
	}

	std::cout << "|----------------------------------------------------------------------------------|";
}

void Lottery::resetSim() {
	for (int i = 0; i < MAX_LOTTERY_TEAMS; i++) {
		lotteryTeams[i].reset();
	}

}