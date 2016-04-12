#include <fstream>
#include <iostream>
#include <time.h>   
#include <stdlib.h>
#include "constants.h"

class Numbers {
private:
	int lotteryNumbers[AMOUNT];
public:
	Numbers();
	~Numbers();

	void run();

	int* getLotteryNumber();

	void generateLotteryNumbers();
	void sort();
};