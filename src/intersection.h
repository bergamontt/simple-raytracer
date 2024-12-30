#pragma once
#include "shapes/sphere.h"
#include <vector>

using namespace std;

class Intersection
{

public:

	Intersection() = default;

	Intersection(float time, const Sphere& s)
		: _time{ time }
		, _s{ s }
	{}

	float time() const { return _time; }
	const Sphere object() const { return _s; };

private:

	float _time;
	Sphere _s;

};

const Intersection