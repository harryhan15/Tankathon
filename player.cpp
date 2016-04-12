#include <iostream>
#include <string.h>
#include "player.h"

Player::Player() {
	name = "";
	projected_pick = 0;
	position = "";
	team = "";
}

Player::~Player() {

}

Player::Player(Player& p) {
	name = p.name;
	projected_pick = p.projected_pick;
	position = p.position;
	team = p.team;
}

std::string Player::getName() {
	return name;
}

std::string Player::getTeam() {
	return team;
}

std::string Player::getPosition() {
	return position;
}

int Player::getProjectedPick() {
	return projected_pick;
}

void Player::createPlayer(std::string n, int pp, std::string pos, std::string t) {
	name = n;
	projected_pick = pp;
	position = pos;
	team = t;
}