#include "helper.h"

double helper::Euclidian_2D (const tspMap& currentMap, const std::vector<int>& x)
{
	double tour_weight = 0;
	unsigned int chromo_size = x.size ();
	for (unsigned int i = 1; i < chromo_size; ++i)
	{
		tour_weight += sqrt (pow (currentMap.points[x[i]].y - currentMap.points[x[i - 1]].y, 2) + pow (currentMap.points[x[i]].x - currentMap.points[x[i - 1]].x, 2));
	}
	return tour_weight;
}
