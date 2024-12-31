#pragma once
#include "shapes/sphere.h"
#include <vector>

using namespace std;

class Intersection
{

public:

	Intersection(float time, const Sphere& s)
		: _time{ time }
		, _sphere{ s }
	{}

	Intersection()
		: _time{ 0.0 }
	{}

	float time() const;
	const Sphere object() const;

private:

	float _time;
	Sphere _sphere;

};

bool operator>(const Intersection& a, const Intersection& b);
bool operator<(const Intersection& a, const Intersection& b);
bool operator==(const Intersection& a, const Intersection& b);
bool operator!=(const Intersection& a, const Intersection& b);