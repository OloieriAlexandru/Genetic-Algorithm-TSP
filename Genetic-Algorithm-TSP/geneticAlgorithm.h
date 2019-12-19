#pragma once

#include <fstream>
#include "tspMap.h"
#include <random>
#include <vector>
#include <iterator>
#include <cmath>
#include <chrono>
#include <utility>
#include <string>

class geneticAlgorithm {
private:
	static int runCount;
	const tspMap & currentMap;
	std::vector<int>mold;
	std::vector<std::vector<int>> pop;
	unsigned int standard_pop_size;
	int number_of_gens;
	int limit;
	double cross_prob, mutation_chance;
	std::vector<int>optimal_tour;
	int optimal_gen;
public:

	geneticAlgorithm (const tspMap& map) : currentMap (map) {
		++runCount;
		standard_pop_size = 100;
		number_of_gens = 500;
		limit = 75;
		cross_prob = 0.3;
		mutation_chance = 0.01;
		optimal_gen = 1;
	}
	void set_param();
	void runGeneticAlgorithm (std::ofstream& fileOut, int runs);
	double Euclidian_2D(const std::vector<int> &x);
	void hypermutation(const int &counter);
	void crossover();
	void evalGen(std::vector<double>& fit);
	unsigned int select1(const std::vector<double> &fs);
	void selection();
	void chromosome_generator(std::vector<int>& val);
	std::vector<int> decodeElem(const std::vector<int> &x);
	void set_mold();
	void init_pop();
	void Genetic_Algorith();
	double calc_f_value();
	unsigned int det_optimal_chromosome();
};

