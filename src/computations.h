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
	}
	
	float time() const;
	const Sphere object() const;
	const Tuple point() const;
	const Tuple eyeVector() const;
	const Tuple normalVector() const;
	bool inside() const;

private:

	const Ray _ray;
	const Sphere _object;

	float _time;

	Tuple _point;
	Tuple _eyeVector;
	Tuple _normalVector;

	bool _inside = false;

	void calculateVectors();
	void negateIfInside();

};