#include "hillClimbingCandidate.h"

bool hillClimbingCandidate::hillClimbingExploration ()
{
	bool foundBetter = false;
	int otherPos, firstPos, secondPos;
	double currentValue;

	for (int i = 0; i < dim; ++i) {
		otherPos = rand () % dim;
		while (otherPos == i) {
			otherPos = rand () % dim;
		}
		swap (currentCandidate[i], currentCandidate[otherPos]);
		currentValue = evaluateCurrentCandidate ();
		if (currentValue < currentIterationBest) {
			currentIterationBest = currentValue;
			foundBetter = true;
			firstPos = i;
			secondPos = otherPos;
		}
		swap (currentCandidate[i], currentCandidate[otherPos]);
	}
	if (foundBetter) {
		swap (currentCandidate[firstPos], currentCandidate[secondPos]);
	}
	return foundBetter;
}

double hillClimbingCandidate::evaluateCurrentCandidate ()
{
	return helper::Euclidian_2D (currentMap, currentCandidate);
}

double hillClimbingCandidate::hillClimbing (std::vector<int>& finalCandidate)
{
	while (hillClimbingExploration ());
	finalCandidate = currentCandidate;
	return currentIterationBest;
}
