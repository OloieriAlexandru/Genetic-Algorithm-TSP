#include "simulatedAnnealing.h"

int simulatedAnnealing::runCount = 0;

std::random_device rd;
std::mt19937 e2 (rd ());
std::uniform_real_distribution<> dist (0, 1);

void simulatedAnnealing::generateRandomCandidate ()
{
	for (int i = 0; i < dim; ++i) {
		currentCandidate[i] = i;
	}
	std::random_shuffle (currentCandidate.begin (), currentCandidate.end ());
	currentIterationBest = evaluateCurrentCandidate ();
}

void simulatedAnnealing::initSimulatedAnnealing ()
{
	temperature = 1000;
}

bool simulatedAnnealing::simulatedAnnealingExploration ()
{
	int otherPos, firstPos, secondPos;
	bool foundBetter = false;
	double currentValue;

	for (int i = 0; i < dim && !foundBetter; ++i) {
		otherPos = rand () % dim;
		while (otherPos == i) {
			otherPos = rand () % dim;
		}
		swap (currentCandidate[i], currentCandidate[otherPos]);
		currentValue = evaluateCurrentCandidate ();
		if (currentValue < currentIterationBest || (dist (e2) < exp (-abs (currentValue - currentIterationBest) / temperature))) {
			currentIterationBest = currentValue;
			foundBetter = true;
			firstPos = i;
			secondPos = otherPos;
		}
		swap (currentCandidate[i], currentCandidate[otherPos]);
	}
	temperature *= 0.9;
	if (foundBetter) {
		swap (currentCandidate[firstPos], currentCandidate[secondPos]);
	}
	return foundBetter;
}

double simulatedAnnealing::evaluateCurrentCandidate ()
{
	return helper::Euclidian_2D (currentMap, currentCandidate);
}

void simulatedAnnealing::runSimulatedAnnealing (std::ofstream & fileOut, int runs)
{
	int iterations = 100;
	bool running = true;
	
	std::cout << "Iterations = 100, do you want to change that? (y/n): ";
	std::string response;
	std::cin >> response;
	while (response != "y" && response != "n") {
		std::cout << "Invalid answer, you should type \"y\" or \"n\": ";
		std::cin >> response;
	}

	if (response == "y") {
		std::cout << "New value for iterations: ";
		std::cin >> iterations;
	}

	std::cout << "\nResults for simulated annealing run no. " + std::to_string (runCount) + ":\n";
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::cout << '\n';
	double weight, time;

	for (int i = 0; i < runs; ++i) {
		std::vector<int> bestCandidate;
		start = std::chrono::system_clock::now ();
		weight = simulatedAnnealingRun (iterations, bestCandidate);
		end = std::chrono::system_clock::now ();
		std::chrono::duration<double> elapsed_seconds = end - start;
		time = elapsed_seconds.count ();
		std::cout << "Iteration " << i << ": found optimal tour with the weight ";
		std::cout << weight << " in " << time << " seconds\n\n";
		for (int i = 0; i < bestCandidate.size (); ++i) {
			fileOut << bestCandidate[i] << ' ';
		}
		fileOut << ';' << weight << ';' << time << '\n';
	}
}

double simulatedAnnealing::simulatedAnnealingRun (int iterations, std::vector<int>& bestCandidate)
{
	double bestRes;
	currentCandidate.resize (dim);
	for (int i = 0; i < iterations; ++i) {
		generateRandomCandidate ();
		initSimulatedAnnealing ();

		while (simulatedAnnealingExploration ());

		if (i == 0) {
			bestRes = currentIterationBest;
			bestCandidate = currentCandidate;
		} else {
			if (currentIterationBest < bestRes) {
				bestRes = currentIterationBest;
				bestCandidate = currentCandidate;
			}
		}
	}
	return bestRes;
}
