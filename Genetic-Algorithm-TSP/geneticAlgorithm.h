#pragma once

#include <fstream>
#include "tspMap.h"

class geneticAlgorithm {
private:
	static int runCount;
	const tspMap & currentMap;
public:

	geneticAlgorithm (const tspMap& map) : currentMap (map) {
		++runCount;
	}

	void runGeneticAlgorithm (std::ofstream& fileOut);
};