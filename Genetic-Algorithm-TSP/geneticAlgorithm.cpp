#include "geneticAlgorithm.h"

int geneticAlgorithm::runCount = 0;

void geneticAlgorithm::runGeneticAlgorithm (std::ofstream & fileOut, int runs)
{
	fileOut << "Results for genetic algorithm run no. " + std::to_string (runCount) + ":\n";
}
