#include <fstream>
#include <iostream>
#include <time.h>   
#include <stdlib.h>
#include "numbers.h"

Numbers::Numbers() {

}

Numbers::~Numbers() {}

void Numbers::run() {
	generateLotteryNumbers();

	sort();
}

int* Numbers::getLotteryNumber() {
	return lotteryNumbers;
}

void Numbers::generateLotteryNumbers() {
	for (int i = 0; i < AMOUNT; i++)
	{
		bool check;
		int n;

		do
		{
			n = rand() % MAX_LOTTERY_TEAMS + 1;

			check = true;
			for (int j = 0; j < i; j++)
				if (n == lotteryNumbers[j])
				{
					check = false;
					break;
				}
		} while (!check);

		lotteryNumbers[i] = n;
	}

	if (lotteryNumbers[0] == 11 && lotteryNumbers[1] == 12 &&
		lotteryNumbers[2] == 13 && lotteryNumbers[3] == 14) {
		generateLotteryNumbers();
	}
}

void Numbers::sort() {
	int temp;

	for (int i = 0; i < AMOUNT; i++) {
		for (int j = 0; j < AMOUNT - 1; j++) {
			if (lotteryNumbers[j] > lotteryNumbers[i]) {
				temp = lotteryNumbers[i];
				lotteryNumbers[i] = lotteryNumbers[j];
				lotteryNumbers[j] = temp;
			}
		}
	}
}