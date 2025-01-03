#pragma once
#include "intersection.h"
#include <optional>
#include <vector>

using namespace std;

class Intersections
{

public:

	Intersections() = default;

	void merge(const Intersections& merged);
	void sort();

	optional<Intersection> hit() const;
	const Intersection get(int index) const;

	int size() const;
	void add(const Intersection& i);

private:

	vector<Intersection> _intersections;

};