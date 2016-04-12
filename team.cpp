#include <iostream>
#include <iomanip>
#include <string.h>
#include "team.h"

using namespace std;

Team::Team() {
	pick_odds = 0.0;
	pick = 0;

	first_pick = 0;
	second_pick = 0;
	third_pick = 0;
}

Team::~Team() {}

Team::Team(Team& t) {
	pick_odds = t.pick_odds;
}

void Team::createTeam(std::string name, double pick, int o) {
	pick_odds = pick;
	this->name = name;
	this->overall = o;
}

std::string Team::getName() {
	return name;
}

double Team::getPickOdds() {
	return pick_odds;
}

void Team::setPick(int pick) {
	this->pick = pick;
}

int Team::getPick() {
	return pick;
}

void Team::setPlayer(Player p) {
	this->p = p;
}

int Team::movement() {
	return overall - pick;
}

void Team::incrementFirstPick() {
	first_pick++;
}

void Team::incrementSecondPick() {
	second_pick++;
}

void Team::incrementThirdPick() {
	third_pick++;
}

void Team::reset() {
	first_pick = 0;
	second_pick = 0;
	third_pick = 0;
}


void Team::display() {
	std::string upperName = nameToUpper(name);

	std::cout << "|" << std::setw(5) << std::left << pick;
	std::cout << std::setw(22) << std::left << upperName << "|";
	std::cout << std::setw(20) << std::left << p.getName() << "|";
	std::cout << std::setw(10) << std::left << p.getPosition() << "|";
	std::cout << std::setw(25) << std::left << p.getTeam() << "|";
	std::cout << std::setw(10) << std::left << movement() << "|\n";
}

void Team::displaySim() {
	std::string upperName = nameToUpper(name);

	std::cout << "|" << std::setw(25) << std::left << upperName << "|";
	std::cout << std::setw(18) << std::left << first_pick << "|";
	std::cout << std::setw(18) << std::left << second_pick << "|";
	std::cout << std::setw(18) << std::left << third_pick << "|\n";
}

std::string Team::nameToUpper(std::string name) {
	std::string ret = "";

	for (int i = 0; i < name.length(); i++) {
		if (name.at(i) == '_') {
			ret+= ' ';
		}
		else {
			ret += toupper(name.at(i));
		}
	}

	return ret;
}