#pragma once

#include "shape.h"
#include <utility>

using namespace std;

class Cube : public Shape
{

public:	
	
	Cube() = default;
	optional<Intersections> localIntersection(const Ray& ray) const override;

private:
	
	const pair<float, float> checkAxis(float origin, float direction) const;
	virtual const Tuple localNormal(const Tuple& point) const;

};