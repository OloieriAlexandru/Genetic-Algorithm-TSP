#pragma once

#include <fstream>
#include "tspMap.h"

class simulatedAnnealing {
private:
	static int runCount;
	const tspMap & currentMap;
public:

	simulatedAnnealing(const tspMap& map) : currentMap (map) {
		++runCount;
	}

	void runSimulatedAnnealing (std::ofstream& fileOut);
};