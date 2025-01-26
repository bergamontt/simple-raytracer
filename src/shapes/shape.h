#pragma once

#include "../matrix.h"
#include "../material.h"
#include "../intersections.h"
#include "../ray.h"

class Shape : public enable_shared_from_this<Shape>
{

public:

	const Tuple normalToWorld(const Tuple& vector) const;
	const Tuple worldToObject(const Tuple& point) const;

	const Tuple normalAt(const Tuple& point) const;
	const Color patternColorAt(const Tuple& p) const;

	bool hasParent() const;

	const ShapePtr& parent() const;
	const Matrix& transform() const;
	const Material& material() const;
	Material& material();

	virtual void setTransform(const Matrix& m);
	void setMaterial(const Material& m);
	void setParent(const ShapePtr& parent);

	virtual optional<Intersections> localIntersection(const Ray& ray) const = 0;

protected:

	Shape(const Matrix& transform, const Material& material)
		: _transform{ transform }
		, _material{ material }
		, _parent{nullptr}
	{}

	Shape() = default;
	virtual ~Shape() = default;

	virtual const Tuple localNormal(const Tuple& point) const = 0;

	Matrix _transform;
	Material _material;
	ShapePtr _parent;

};