#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

template<typename T>
struct point {
	T x, y;
	point (T px, T py) {
		x = px;
		y = py;
	}
};

template<typename T>
class tspMap {
private:
	std::vector<point<T>>points;
public:
	void loadMap (std::string path);
};

template<typename T>
inline void tspMap<T>::loadMap (std::string path)
{
	std::ifstream fileIn (path);
	std::string currentLine;

	T x, y;
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
