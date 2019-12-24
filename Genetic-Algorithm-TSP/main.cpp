#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "tsp.h"

const char* mapsPath = "maps.txt";
const char* errorMessage = "Errorr!\n";

void listOptions ();
void listMaps ();
void addMap (const std::string& name, const std::string& path);
std::string getPath (const std::string& name);

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
	std::cout << "4. quit\n";
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