#pragma once
#include "shape.h"
#include "../constants.h"

class Sphere : public Shape
{
public:

	Sphere()
		: _thisID{ ++_ID }
		, _radius{ 1.0f }
		, _origin{ createPoint(0.0f, 0.0f, 0.0f) }
	{}

	Sphere(const Sphere& s)
		: Shape(s._transform, s._material)
		, _radius{ s._radius }
		, _origin{ s._origin }
		, _thisID{ s._ID }
	{}

	const Tuple origin() const;
	const float radius() const;
	const int id() const;

	optional<Intersections> localIntersection(const Ray& ray) const;

protected:

	const Tuple localNormal(const Tuple& point) const override;

private:

	float _radius;
	Tuple _origin;

	int _thisID;
	inline static int _ID;

};

bool operator==(const Sphere& a, const Sphere& b);