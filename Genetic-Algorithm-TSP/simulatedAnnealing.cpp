#include "simulatedAnnealing.h"

int simulatedAnnealing::runCount = 0;

void simulatedAnnealing::runSimulatedAnnealing (std::ofstream & fileOut)
{
	fileOut << "Results for simulated annealing run no. " + std::to_string (runCount) + ":\n";
}
