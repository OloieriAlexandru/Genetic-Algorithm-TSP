#include "tsp.h"

void tsp::listOptions ()
{
	std::cout << "1. ga/genetic (starts genetic algorithm for current map)\n";
	std::cout << "2. sa/simulated (starts genetic algorithm for current map)\n";
	std::cout << "3. newruns (allows you to change the number of runs)\n";
	std::cout << "4. listruns (print the current number of runs)\n";
	std::cout << "5. stop (return to main menu)\n";
}

std::string tsp::getNewFileName (){
	int id = rand ();
	return "results/tsp" + std::to_string (id) + ".txt";
}

tsp::tsp (const std::string & mapPath){
	currentMap.loadMap (mapPath);
}

void tsp::run (int runs){
	bool running = true;
	std::string currentFileName = getNewFileName ();
	std::ofstream fileOut (currentFileName);
	listOptions ();
	while (running) {
		std::string command;
		std::cout << "	tsp: ";
		std::cin >> command;
		if (command == "ga" || command == "genetic") {
			geneticAlgorithm ga(currentMap);
			ga.runGeneticAlgorithm (fileOut, runs);
			listOptions ();
		}
		else if (command == "sa" || command == "simulated") {
			simulatedAnnealing sa (currentMap);
			sa.runSimulatedAnnealing (fileOut, runs);
			listOptions ();
		}
		else if (command == "newruns") {
			std::cout << "runs = " << runs << ", new runs = ";
			std::cin >> runs;
		} 
		else if (command == "listruns") {
			std::cout << "runs = " << runs << '\n';
		}
		else if (command == "stop") {
			running = false;
		}
	}

	fileOut.close ();
}
