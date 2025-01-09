#pragma once
#include "types.h"

using namespace std;

class Intersection
{

public:

	Intersection(float time, const ShapeConstPtr& s)
		: _time{ time }
		, _object{ s }
	{}

	Intersection()
		: _time{ 0.0 }
	{}

	float time() const;
	const ShapeConstPtr& object() const;

private:

	float _time;
	ShapeConstPtr _object;

};

bool operator>(const Intersection& a, const Intersection& b);
bool operator<(const Intersection& a, const Intersection& b);
bool operator==(const Intersection& a, const Intersection& b);
bool operator!=(const Intersection& a, const Intersection& b);