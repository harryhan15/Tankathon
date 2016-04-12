#include <fstream>
#include <iostream>
#include <time.h>   
#include <stdlib.h>
#include "player.h"
#include "lottery.h"
#include "numbers.h"
#include "constants.h"

class Generate {
private:
	Player player[TOTAL_TEAMS];
	Lottery lottery;
	Numbers number;
public:
	Generate();
	~Generate();

	void run();

	void reset();
	void initializeSim();
	void runSim();

	void generatePlayer();
	void count();

	void display();
	void displaySim();

	void resetSim();
};