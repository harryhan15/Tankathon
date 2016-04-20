#include <fstream>
#include <iostream>
#include <time.h>   
#include <stdlib.h>
#include "generate.h"

int main()
{
	std::cout << "Welcome to the Tankathon!\n";
	Generate g;

	int input;
	bool valid = false;

	while (!valid) {
		std::cout << "1. Run simulation once and output draft chart\n";
		std::cout << "2. Run simulation multiple times and print statistics\n";
		std::cout << "0. Exit\n\n";

		std::cin >> input;
		switch (input) {
		case 0:
			std::cout << "\nExiting...\n\n";
			valid = true;
			break;
		case 1:
		{
			std::cout << "\nSimulating NHL draft lottery...";
			g.run();
			g.display();
			g.reset();
			std::cout << "\n\n--------------------------------------------------------------------------------------------------\n\n";
			break;
		}
		case 2:
		{
			int num = 0;

			std::cout << "\nEnter number of times to run simulation: ";
			std::cin >> num;
			std::cout << "\n";
			
			for (int i = 0; i < num; i++) {
				std::cout << "\r" << i + 1 << " Simulation(s) Complete...";
				std::cout.flush();
				
				g.initializeSim();
				g.runSim();
				g.count();
				g.reset();
			}
			std::cout << "\n\nAfter simulating the lottery " << num << " time(s), the results are: \n\n";

			g.displaySim();
			g.resetSim();
			std::cout << "\n\n--------------------------------------------------------------------------------------------------\n\n";
			break;
		}
		default:
		{
			std::cout << "\nError. Please Try Again.\n\n";
			break;
		}
		}
	}
	
	return 0;
}