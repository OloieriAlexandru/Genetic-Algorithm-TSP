#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

struct point {
	double x, y;
	point (double px, double py) {
		x = px;
		y = py;
	}

	friend std::ostream& operator<<(std::ostream& out, const point& p);
};

class tspMap {
public:
	std::vector<point>			points;
	void						loadMap (std::string path);

	friend std::ostream& operator<<(std::ostream& out, const tspMap& mp);
};
