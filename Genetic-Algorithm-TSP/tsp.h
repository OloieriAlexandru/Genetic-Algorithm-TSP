#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "tspMap.h"
#include "geneticAlgorithm.h"
#include "simulatedAnnealing.h"

class tsp {
private:
	tspMap currentMap;
	std::string getNewFileName ();
public:
	tsp (const std::string& mapPath);

	void run (int runs = 30);
};