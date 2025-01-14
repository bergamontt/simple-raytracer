#pragma once
#include "ray.h"
#include "intersection.h"
#include "shapes/sphere.h"

class Computations
{

public:

	Computations(const Intersection& intrs,
		const Ray& ray)
		: _ray{ ray }
		, _object{ intrs.object() }
		, _time{ intrs.time() }
	{
		calculateVectors();
		negateIfInside();
		calculateOverPoint();
	}

	float time() const;
	const ShapeConstPtr& object() const;
	const Tuple& point() const;
	const Tuple& eyeVector() const;
	const Tuple& normalVector() const;
	const Tuple& overPoint() const;
	const Tuple& reflectVector() const;
	bool inside() const;

private:

	const Ray _ray;
	const ShapeConstPtr& _object;

	float _time;

	Tuple _point;
	Tuple _overPoint;
	Tuple _eyeVector;
	Tuple _normalVector;
	Tuple _reflectVector;

	bool _inside = false;

	void calculateVectors();
	void negateIfInside();
	void calculateOverPoint();

};