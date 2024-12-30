#pragma once
#include "intersection.h"

class Intersections
{
public:

	Intersections(int n)
		: _array{ new Intersection[n] }
	{}

private:

	Intersection* _array;
	int _n;

};