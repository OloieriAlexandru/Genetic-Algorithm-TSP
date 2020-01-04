#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <vector>
#include <cmath>

#include "tsp.h"

#define	fi	first
#define se	second

const char* mapsPath = "maps.txt";
const char* errorMessage = "Errorr!\n";

void		listOptions ();
void		listMaps ();
void		addMap (const std::string& name, const std::string& path);
std::string	getPath (const std::string& name);
double		distance (const std::pair<double, double>& p1, const std::pair<double, double>& p2);
void		optimumDistanceCalculator ();

int main() {
	srand (time (NULL));
	listOptions ();
	while (true) {
		std::string command;
		std::cout << "menu: ";
		std::cin >> command;
		if (command == "run") {
			std::string name;
			std::cin >> name;
			std::string mapPath = getPath (name);
			if (mapPath.size ()) {
				tsp thisTsp(mapPath);
				thisTsp.run ();
				listOptions ();
			}
			else {
				std::cout << "Invalid name!\n";
			}
		} 
		else if (command == "list") {
			listMaps ();
		} 
		else if (command == "add") {
			std::string name, path;
			std::cout << "mapName mapPath\n";
			std::cin >> name >> path;
			addMap (name, path);
		}
		else if (command == "optimum") {
			optimumDistanceCalculator ();
		}
		else if (command == "quit" || command == "q") {
			break;
		}
		else {
			listOptions ();
		}
	}
	return 0;
}

void listOptions () {
	std::cout << "1. run mapName\n";
	std::cout << "2. list (all the maps)\n";
	std::cout << "3. add (a new map)\n";
	std::cout << "4. optimum (optimum distance calculator)\n"; 
	std::cout << "5. quit\n";
}

void listMaps () {
	std::ifstream fileIn (mapsPath);
	if (fileIn.is_open ()) {
		int no = 1;
		std::string name, path;
		while (fileIn >> name) {
			fileIn >> path;
			std::cout << name << ' ' << path << '\n';
		}
	}
	else {
		std::cout << errorMessage;
	}
}

void addMap (const std::string& name, const std::string& path) {
	std::ofstream fileOut (mapsPath, std::fstream::app);
	fileOut << name << ' ' << path << '\n';
	fileOut.close ();
}

std::string getPath (const std::string& name) {
	std::ifstream fileIn (mapsPath);
	if (fileIn.is_open ()) {
		int no = 1;
		std::string currName, path;
		while (fileIn >> currName) {
			fileIn >> path;
			if (name == currName) {
				return path;
			}
		}
	}
	return "";
}

double distance (const std::pair<double, double>& p1, const std::pair<double, double>& p2) {
	return sqrt ((p2.fi - p1.fi)*(p2.fi - p1.fi) + (p2.se - p1.se)*(p2.se - p1.se));
}

void optimumDistanceCalculator () {
	int n;
	std::string skip;
	std::vector<std::pair<double, double>> points;
	std::vector<int> optimumPerm;
	std::cout << "Enter the number of points: ";
	std::cin >> n;
	points.resize (n);
	std::cout << "Enter the points:\n";
	for (int i = 0; i < n; ++i) {
		std::cin >> skip >> points[i].first >> points[i].second;
	}
	optimumPerm.resize (n);
	std::cout << "Enter the optimum permutation: \n";
	for (int i = 0; i < n; ++i) {
		std::cin >> optimumPerm[i];
		--optimumPerm[i];
	}
	double res = 0;
	for (int i = 0; i < n - 1; ++i) {
		res += distance (points[optimumPerm[i]], points[optimumPerm[i + 1]]);
	}
	res += distance (points[optimumPerm[0]], points[optimumPerm[n - 1]]);
	std::cout << "The optimum distance for the map is " << res << '\n';
}