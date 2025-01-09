#pragma once

#include "../matrix.h"
#include "../material.h"
#include "../intersections.h"
#include "../ray.h"

class Shape : public enable_shared_from_this<Shape>
{

public:

	const Tuple normalAt(const Tuple& point) const;

	const Matrix& transform() const;
	const Material& material() const;

	void setTransform(const Matrix& m);
	void setMaterial(const Material& m);

	virtual optional<Intersections> localIntersection(const Ray& ray) const = 0;

protected:

	Shape(const Matrix& transform, const Material& material)
		: _transform{ transform }
		, _material{ material }
	{}

	Shape() = default;
	virtual ~Shape() = default;

	virtual const Tuple localNormal(const Tuple& point) const = 0;

	Matrix _transform;
	Material _material;

};