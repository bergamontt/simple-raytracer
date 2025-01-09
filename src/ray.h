#pragma once

#include "intersections.h"
#include "tuple.h"

class Matrix;

using namespace std;

class Ray
{
public:
	
	Ray(const Tuple& origin, const Tuple& direction)
		: _origin{ origin }
		, _direction{ direction }
	{}

	const Tuple origin() const;
	const Tuple direction() const;

	const Tuple position(float time) const;
	const Ray transform(const Matrix& m) const;

	optional<Intersections> intersect(const ShapePtr& sph) const;

private:
	Tuple _origin;
	Tuple _direction;
};
