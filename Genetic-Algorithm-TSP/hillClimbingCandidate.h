#pragma once

#include <vector>

#include "tspMap.h"
#include "helper.h"

class hillClimbingCandidate {
private:
	const tspMap &		currentMap;
	double				currentIterationBest;
	std::vector<int>	currentCandidate;
	int					dim;

	bool			hillClimbingExploration ();
	double			evaluateCurrentCandidate ();
public:
	hillClimbingCandidate (const tspMap& map, const std::vector<int> candidate) : currentMap (map) {
		currentCandidate = candidate;
		currentIterationBest = evaluateCurrentCandidate ();
		dim = candidate.size ();
	}

	double hillClimbing (std::vector<int>& finalCandidate);
};