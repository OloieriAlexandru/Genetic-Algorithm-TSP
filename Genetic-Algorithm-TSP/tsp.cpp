#include "tsp.h"

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

	while (running) {
		std::string command;
		std::cout << "	tsp: ";
		std::cin >> command;
		if (command == "ga" || command == "genetic") {
			geneticAlgorithm ga(currentMap);
			ga.runGeneticAlgorithm (fileOut);
		}
		else if (command == "sa" || command == "simulated") {
			simulatedAnnealing sa (currentMap);
			sa.runSimulatedAnnealing (fileOut);
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
