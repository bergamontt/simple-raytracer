#pragma once
#include "shape.h"

class Cylinder : public Shape
{

public:

	Cylinder()
		: _minimum{ -INFINITY }
		, _maximum{ INFINITY }
		, _capped{ false }
	{}

	float minimum() const;
	float maximum() const;
	bool capped() const;

	void setMinimum(const float min);
	void setMaximum(const float max);
	void setCapped(const bool capped);

	optional<Intersections> localIntersection(const Ray& ray) const override;

private:
	
	float _minimum;
	float _maximum;

	bool _capped;

	bool hitsCap(const Ray& ray, const float time) const;
	optional<Intersections> capIntersection(const Ray& ray) const;

	virtual const Tuple localNormal(const Tuple& point) const;

};