#pragma once

#include <fstream>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <random>

#include "tspMap.h"
#include "helper.h"

class simulatedAnnealing {
private:
	static int			runCount;
	const tspMap &		currentMap;

	int					dim;
	double				temperature;
	double				currentIterationBest;
	std::vector<int>	currentCandidate;

	void				generateRandomCandidate ();
	void				initSimulatedAnnealing ();
	bool				simulatedAnnealingExploration ();

	double				evaluateCurrentCandidate ();
public:
	simulatedAnnealing(const tspMap& map) : currentMap (map) {
		++runCount;
		dim = currentMap.points.size ();
	}

	void				runSimulatedAnnealing (std::ofstream& fileOut, int runs);

	double				simulatedAnnealingRun (int iterations, std::vector<int>& bestCandidate);
};