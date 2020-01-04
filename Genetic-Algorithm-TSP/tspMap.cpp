#include "tspMap.h"

void tspMap::loadMap(std::string path) {
	std::ifstream fileIn(path);
	std::string currentLine;

	double x, y;
	int id;

	while (std::getline(fileIn, currentLine)) {
		if (currentLine == "NODE_COORD_SECTION") {
			break;
		}
	}

	points.clear ();
	while (fileIn >> currentLine) {
		if (currentLine == "EOF") {
			break;
		}
		fileIn >> x >> y;
		points.emplace_back(x, y);
	}

	fileIn.close();
}

std::ostream & operator<<(std::ostream & out, const point & p)
{
	out << p.x << ' ' << p.y;
	return out;
}

std::ostream & operator<<(std::ostream & out, const tspMap & mp)
{
	out << mp.points.size () << '\n';
	for (auto& point : mp.points) {
		out << point << '\n';
	}
	return out;
}
