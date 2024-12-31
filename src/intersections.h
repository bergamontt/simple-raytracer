#pragma once
#include "intersection.h"
#include <optional>
#include <vector>

using namespace std;

class Intersections
{

public:

	Intersections() = default;

	const Intersection get(int index) const;
	optional<Intersection> hit() const;

	void add(const Intersection& i);
	int size() const;

private:

	vector<Intersection> _intersections;

};