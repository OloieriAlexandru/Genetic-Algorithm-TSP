#pragma once
#include <cmath>
#include <vector>

#include "tspMap.h"

#define swap(a, b) a^=b,b^=a,a^=b

namespace helper
{
	double Euclidian_2D (const tspMap& currentMap, const std::vector<int> &x);
}