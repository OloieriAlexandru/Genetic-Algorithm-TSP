#include "tspMap.h"

void tspMap::loadMap (std::string path){
	std::ifstream fileIn (path);
	std::string currentLine;

	double x, y;
	int id;

	while (std::getline (fileIn, currentLine)) {
		if (currentLine == "NODE_COORD_SECTION") {
			break;
		}
	}

	while (fileIn >> currentLine) {
		if (currentLine == "EOF") {
			break;
		}
		fileIn >> x >> y;
		points.emplace_back (x, y);
	}

	fileIn.close ();
}
