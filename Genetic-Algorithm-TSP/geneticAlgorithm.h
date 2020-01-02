#pragma once

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <iterator>
#include <cmath>
#include <chrono>
#include <utility>
#include <string>
#include <queue>
#include <functional>
#include <ostream>

struct elitismCandidate {
	double	value;
	int		position;
	elitismCandidate() { }
	elitismCandidate (double v, int p) : value (v), position (p) { }
	friend bool operator>(const elitismCandidate& c1, const elitismCandidate& c2);
	friend std::ostream& operator<<(std::ostream& out, const elitismCandidate& c);
};

#include "helper.h"
#include "tspMap.h"
#include "hillClimbingCandidate.h"

class geneticAlgorithm {
private:
	static int							runCount;
	const tspMap &						currentMap;

	unsigned int						standard_pop_size;
	int									number_of_gens;
	int									limit;
	int									optimal_gen;
	std::vector<int>					optimal_tour;
	std::vector<int>					mold;
	std::vector<std::vector<int>>		pop;
	double								cross_prob, mutation_chance, elitism_rate;
public:
	geneticAlgorithm (const tspMap& map) : currentMap (map) {
		++runCount;
		standard_pop_size = 100;
		number_of_gens = 1500;
		limit = 350;
		elitism_rate = 0.10;
		cross_prob = 0.35;
		mutation_chance = 0.015;
		optimal_gen = 1;
	}

	void						set_param();
	void						runGeneticAlgorithm (std::ofstream& fileOut, int runs);
	void						hypermutation(const int &counter);
	void						crossover();
	void						evalGen(std::vector<double>& fit);
	void						selection();
	void						chromosome_generator(std::vector<int>& val);
	void						set_mold ();
	void						init_pop ();
	void						Genetic_Algorith ();
	
	std::vector<int>			decodeElem(const std::vector<int> &x);
	double						calc_f_value();

	unsigned int				select1 (const std::vector<double> &fs);
	unsigned int				det_optimal_chromosome();
};

