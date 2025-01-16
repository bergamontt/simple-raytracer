#pragma once
#include "ray.h"
#include "intersection.h"
#include "shapes/sphere.h"

class Computations
{

public:

	Computations(const Intersection& intrs,
		const Ray& ray, const Intersections& xs)
		: _ray{ ray }
		, _object{ intrs.object() }
		, _time{ intrs.time() }
	{
		calculateVectors();
		negateIfInside();
		calculateOverPoint();
		calculateUnderPoint();
		calculateIndeces(intrs, xs);
	}

	Computations(const Intersection& intrs,
		const Ray& ray)
		: _ray{ ray }
		, _object{ intrs.object() }
		, _time{ intrs.time() }
	{
		calculateVectors();
		negateIfInside();
		calculateOverPoint();
		calculateUnderPoint();
		calculateDefaultIndeces(intrs);
	}

	float time() const;
	float n1() const;
	float n2() const;

	const ShapeConstPtr& object() const;
	const Tuple& point() const;
	const Tuple& eyeVector() const;
	const Tuple& normalVector() const;
	const Tuple& overPoint() const;
	const Tuple& underPoint() const;
	const Tuple& reflectVector() const;
	bool inside() const;

private:

	const Ray _ray;
	const ShapeConstPtr& _object;

	float _time;

	float _n1;
	float _n2;

	Tuple _point;
	Tuple _overPoint;
	Tuple _underPoint;
	Tuple _eyeVector;
	Tuple _normalVector;
	Tuple _reflectVector;

	bool _inside = false;

	void calculateVectors();
	void negateIfInside();
	void calculateOverPoint();
	void calculateUnderPoint();

	void calculateIndeces(const Intersection& intrs,
						  const Intersections& xs);
	void calculateDefaultIndeces(const Intersection& intrs);
};