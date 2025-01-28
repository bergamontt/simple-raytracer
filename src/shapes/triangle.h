#pragma once
#include "shape.h"

class Triangle : public Shape
{
public:

	Triangle(const Tuple& p1,
			 const Tuple& p2,
			 const Tuple& p3)
		: _p1{p1}
		, _p2{p2}
		, _p3{p3}
		, _e1{p2 - p1}
		, _e2{p3 - p1}
		, _normal{normalize(cross(_e2, _e1))}
	{}

	Triangle(const Triangle& src)
		: _p1{ src._p1 }
		, _p2{ src._p2 }
		, _p3{ src._p3 }
		, _e1{ src._e1 }
		, _e2{ src._e2 }
		, _normal{src._normal}
	{}

	Triangle()
		: Triangle( { 0.0f, 0.0f },
				    { 0.0f, 0.0f },
				    { 0.0f, 0.0f })
	{}

	const Tuple& fstPoint() const;
	const Tuple& scdPoint() const;
	const Tuple& trdPoint() const;

	const Tuple& fstEdgeVector() const;
	const Tuple& scdEdgeVector() const;

	optional<Intersections> localIntersection(const Ray& ray) const override;

private:

	Tuple _p1, _p2, _p3;
	Tuple _e1, _e2;
	Tuple _normal;

	const Tuple localNormal(const Tuple& point) const override;

};