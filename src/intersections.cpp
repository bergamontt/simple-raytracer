#include "intersections.h"

const Intersection Intersections::get(int index) const
{
	return _intersections.at(index);
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
}

int Intersections::size() const
{
	return _intersections.size();
}