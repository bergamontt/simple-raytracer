#pragma once
#include "shape.h"

class Plane : public Shape
{

public:
	
	Plane() = default;
	optional<Intersections> localIntersection(const Ray& ray) const override;

protected:

	const Tuple localNormal(const Tuple& point) const override;

};