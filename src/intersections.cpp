#include "intersections.h"
#include <algorithm> 

const Intersection& Intersections::get(int index) const
{
	return _intersections.at(index);
}

void Intersections::merge(const Intersections& merged)
{
	for (const Intersection& intersection : merged._intersections)
		add(intersection);
	sort();
}

void Intersections::sort()
{
	std::sort(_intersections.begin(), _intersections.end());
}

optional<Intersection> Intersections::hit() const
{
	int hitIndex = -1;
	for (int i = 0; i < _intersections.size(); ++i)
	{
		Intersection currIntr = get(i);
		if (currIntr.time() < 0)
			continue;

		if (hitIndex == -1 || get(hitIndex) > currIntr)
			hitIndex = i;
	}

	if (hitIndex == -1)
		return {};
	return get(hitIndex);
}


void Intersections::add(const Intersection& i)
{
	_intersections.emplace_back(i);
	sort();
}

int Intersections::size() const
{
	return _intersections.size();
}