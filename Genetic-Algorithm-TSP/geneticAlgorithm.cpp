#include "geneticAlgorithm.h"

int geneticAlgorithm::runCount = 0;
std::mt19937 gen(std::random_device{}());

void geneticAlgorithm::runGeneticAlgorithm (std::ofstream & fileOut, int runs)
{
	std::string answer;
	unsigned int dec_size = currentMap.points.size();
	
	std::cout << "------------------------------------------------------------------\n\n";
	std::cout << "Do you wish to proceed with the following parameters:\n";
	std::cout << "Population size: " << standard_pop_size << "\tNumber of generations: " << number_of_gens<< "\tHypermutation mark: " << limit
		<< "\tElitism rate: " << elitism_rate << "\tMutation chance: " << mutation_chance << "\tCrossover chance: " << cross_prob << "? (y/n)\t";
	
	std::cin >> answer;
	while(answer != "y" and answer != "n")
	{
		std::cout << "I did not understand! Please state your answer again! (y/n)\t";
		std::cin >> answer;
	}
	if(answer == "n")
	{
		set_param();
		std::cout << "Changes done! The parameters are now:\n";
		std::cout << "Population size: " << standard_pop_size << "\tNumber of generations: " << number_of_gens << "\tHypermutation mark: " << limit
			<< "\tElitism rate: " << elitism_rate << "\tMutation chance: " << mutation_chance << "\tCrossover chance: " << cross_prob << "\n";
	}
	else
		std::cout << "The parameters were not modified!\n";
	
	std::cout << "\nResults for genetic algorithm run no. " + std::to_string (runCount) + ":\n";
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::cout << std::endl;
	double weight, time;
	int dim;

	fileOut << "ga\n";
	for (int i = 1; i <= runs; ++i)
	{
		start = std::chrono::system_clock::now();
		Genetic_Algorith();
		hillClimbingCandidate result(currentMap, optimal_tour);
		weight = result.hillClimbing(optimal_tour);
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		time = elapsed_seconds.count();
		std::cout << "Iteration " << i << ": found optimal tour ";
		dim = optimal_tour.size();
		for (unsigned int j = 0; j < dim - 1; ++j)
		{
			std::cout << optimal_tour[j] << " | ";
		}
		std::cout << optimal_tour[dim - 1] << " with the weight " << weight
			<< " in " << time << " seconds." << std::endl << std::endl;
		fileOut << weight << ';' << time << std::endl;
	}
	std::cout << "------------------------------------------------------------------\n";
}

void geneticAlgorithm::chromosome_generator(std::vector<int>& val)
{
	std::uniform_int_distribution<> dist;
	int n = currentMap.points.size();
	for (int i = 0; i < n - 1; ++i)
	{
		dist = std::uniform_int_distribution<>(0, n - i - 1);
		val.emplace_back(dist(gen));
	}
	val.emplace_back(0);
}

std::vector<int> geneticAlgorithm::decodeElem(const std::vector<int> &x)
{
	std::vector<int> result;
	auto it = mold.begin();
	int n = currentMap.points.size();
	for (int i = 0; i < n; ++i)
	{
		result.emplace_back(mold[x[i]]);
		mold.erase(it + x[i]);
		it = mold.begin();
	}
	set_mold();
	return result;
}

void geneticAlgorithm::set_mold()
{
	int n = currentMap.points.size();
	for (int i = 0; i <= n - 1; ++i)
		mold.emplace_back(i);
}

void geneticAlgorithm::init_pop()
{
	unsigned int pop_size = standard_pop_size;
	pop.resize(pop_size);
	for (unsigned int i = 0; i < pop_size; ++i)
		chromosome_generator(pop[i]);
}

void geneticAlgorithm::hypermutation(const int &counter)
{
	std::uniform_real_distribution<> dist(0, 1);
	double mutation_prob;
	if (counter < limit)
		mutation_prob = mutation_chance;
	else
		mutation_prob = 0.5;
	unsigned int pop_size = pop.size(), chromosome_size = currentMap.points.size();
	for (unsigned int i = 0; i < pop_size; ++i)
		for (unsigned int j = 0; j < chromosome_size - 1; ++j)
			if (dist(gen) < mutation_prob)
			{
				pop[i][j] = (pop[i][j] + 1) % (chromosome_size - j - 1);
			}		
}

void geneticAlgorithm::crossover()
{	
	std::vector<double> crossover_chance;
	int i, j, size; std::vector<int> aux_pop;
	double aux_chance;
	size = pop[0].size();
	std::uniform_real_distribution<> dist(0, 1);
	std::uniform_int_distribution<> distint(0, size - 2);
	std::bernoulli_distribution distber;
	int pop_size = pop.size();
	for (i = 0; i < pop_size; ++i)
		crossover_chance.push_back(dist(gen));
	for (i = 1; i < pop_size; ++i)
	{
		aux_pop = pop[i];
		aux_chance = crossover_chance[i];
		j = i - 1;
		while (j >= 0 && crossover_chance[j] > aux_chance)
		{
			pop[j + 1] = pop[j];
			crossover_chance[j + 1] = crossover_chance[j];
			j--;
		}
		pop[j + 1] = aux_pop;
		crossover_chance[j + 1] = aux_chance;
	}
	int crossover_candidates_nr = 0;
	double crossover_p = cross_prob;
	i = 0;
	while (crossover_chance[i] < crossover_p && i < pop_size)
	{
		crossover_candidates_nr++;
		i++;
	}
	std::vector<std::vector<int>> children;
	bool last_chromosome_chance;
	if (crossover_candidates_nr % 2 == 0)
	{
		children.resize(crossover_candidates_nr);
		for (i = 1; i < crossover_candidates_nr; i = i + 2)
		{
			int pos = distint(gen);
			children[i - 1] = pop[i - 1];
			children[i] = pop[i];
			for (j = pos; j < size; ++j)
			{
				children[i - 1][j] = pop[i][j];
				children[i][j] = pop[i - 1][j];
			}
		}
	}
	else
	{
		last_chromosome_chance = distber(gen);
		if (last_chromosome_chance == true)
		{
			crossover_candidates_nr++;
			children.resize(crossover_candidates_nr);
			for (i = 1; i < crossover_candidates_nr; i = i + 2)
			{
				int pos = distint(gen);
				children[i - 1] = pop[i - 1];
				children[i] = pop[i];
				for (j = pos; j < size; ++j)
				{
					children[i - 1][j] = pop[i][j];
					children[i][j] = pop[i - 1][j];
				}
			}
		}
		else
		{
			children.resize(crossover_candidates_nr - 1);
			for (i = 1; i < crossover_candidates_nr - 1; i = i + 2)
			{
				int pos = distint(gen);
				children[i - 1] = pop[i - 1];
				children[i] = pop[i];
				for (j = pos; j < size; ++j)
				{
					children[i - 1][j] = pop[i][j];
					children[i][j] = pop[i - 1][j];
				}
			}
		}
	}
	for (i = 0; i < children.size(); ++i)
		pop.push_back(children[i]);
}

void geneticAlgorithm::evalGen(std::vector<double>& fit)
{
	unsigned int i;
	unsigned int pop_size = pop.size();
	//double aux;
	//double maxi_f = helper::Euclidian_2D(currentMap, decodeElem(pop[0]));
	for (i = 0; i < pop_size; ++i)
	{
		fit.push_back(1/(0.00001 + helper::Euclidian_2D(currentMap, decodeElem(pop[i]))));
	}
	/*for (i = 1; i < pop.size(); ++i)
	{
		aux = helper::Euclidian_2D (currentMap, decodeElem(pop[i]));
		if (aux > maxi_f)
			maxi_f = aux;
	}
	for (i = 0; i < pop.size(); ++i)
		fit.push_back(1.1 * maxi_f - helper::Euclidian_2D (currentMap, decodeElem(pop[i])));*/
}

unsigned int geneticAlgorithm::select1(const std::vector<double> &fs)
{
	std::uniform_real_distribution<> dist(0, 1);
	double probability = dist(gen) * fs.back();
	for (unsigned int i = 0; i < fs.size(); ++i)
		if (probability <= fs[i])
			return i;
}

void geneticAlgorithm::selection()
{
	std::vector<double> fit;
	unsigned int i;
	unsigned int poz;
	std::vector<std::vector<int>> newpop;
	unsigned int elitism_candidates_num = floor(elitism_rate * standard_pop_size);
	std::priority_queue<elitismCandidate, std::vector<elitismCandidate>, std::greater<elitismCandidate> >pq;
	evalGen (fit);
	for (int i = 0; i < pop.size (); ++i) {
		pq.push (elitismCandidate (fit[i], i));
		if (pq.size () > elitism_candidates_num) {
			pq.pop ();
		}
	}
	while (!pq.empty ()) {
		newpop.push_back (pop[pq.top ().position]);
		pq.pop ();
	}
	std::vector<double> fs;
	fs.emplace_back(fit[0]);
	for (i = 1; i < pop.size(); ++i)
		fs.emplace_back(fs[i - 1] + fit[i]);
	for (i = elitism_candidates_num; i < standard_pop_size; ++i)
		newpop.emplace_back(pop[select1(fs)]);
	pop = newpop;
}

void geneticAlgorithm::Genetic_Algorith()
{
	init_pop();
	set_mold();
	int i = 1;
	optimal_tour = decodeElem(pop[det_optimal_chromosome()]);
	unsigned opt_poz;
	double best_sol = helper::Euclidian_2D (currentMap, optimal_tour);
	int counter = 1;
	double possible_sol;
	while (i <= number_of_gens)
	{
		hypermutation(counter);
		crossover();
		selection();
		opt_poz = det_optimal_chromosome();
		if (counter == limit)
			best_sol = helper::Euclidian_2D (currentMap, decodeElem(pop[opt_poz]));
		possible_sol = helper::Euclidian_2D (currentMap, decodeElem(pop[opt_poz]));
		i++;
		if (possible_sol < best_sol)
		{
			best_sol = possible_sol;
			if(helper::Euclidian_2D (currentMap, optimal_tour) > best_sol)
			{
				optimal_tour = decodeElem(pop[opt_poz]);
			}
			optimal_gen = i;
			counter = 1;
		}
		else
			counter++;
	}
}

void geneticAlgorithm::set_param()
{
	std::cout << "Give new population size: ";
	std::cin >> standard_pop_size;
	std::cout << "Give new number of generations: ";
	std::cin >> number_of_gens;
	std::cout << "Give new hypermutation mark: ";
	std::cin >> limit;
	std::cout << "Give new elitism rate: ";
	std::cin >> elitism_rate;
	std::cout << "Give new mutation chance: ";
	std::cin >> mutation_chance;
	std::cout << "Give new crossover chance: ";
	std::cin >> cross_prob;
}

unsigned int geneticAlgorithm::det_optimal_chromosome()
{
	unsigned int poz = 0;
	double minimum = helper::Euclidian_2D (currentMap, decodeElem(pop[0]));
	double aux;
	for (unsigned int j = 1; j < pop.size(); j++)
	{
		aux = helper::Euclidian_2D (currentMap, decodeElem(pop[j]));
		if (minimum > aux)
		{
			minimum = aux;
			poz = j;
		}
	}
	return poz;
}

double geneticAlgorithm::calc_f_value()
{
	unsigned int pop_size = pop.size();
	double sol = helper::Euclidian_2D (currentMap, decodeElem(pop[0]));
	double aux;
	for (unsigned int j = 1; j < pop_size; j++)
	{
		aux = helper::Euclidian_2D (currentMap, decodeElem(pop[j]));
		if (sol > aux)
			sol = aux;
	}		
	return sol;
}

bool operator>(const elitismCandidate & c1, const elitismCandidate & c2)
{
	return c1.value > c2.value;
}

std::ostream & operator<<(std::ostream & out, const elitismCandidate & c)
{
	out << c.position << ' ' << c.value;
	return out;
}
