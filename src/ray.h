#pragma once
#include "shapes/sphere.h"
#include "intersection.h"
#include <vector>

using namespace std;

class Ray {
public:
	
	Ray(const Tuple& origin, const Tuple& direction)
		: _origin{ origin }
		, _direction{ direction }
	{}

	const Tuple origin() const;
	const Tuple direction() const;

	const Tuple position(float time) const;

	vector<Intersection> intersect(const Sphere& sph) const;

private:
	Tuple _origin;
	Tuple _direction;
};
