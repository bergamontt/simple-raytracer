#include <cmath>
#include "ray.h"
#include "matrix.h"
#include "shapes/shape.h"

using namespace std;

const Tuple& Ray::origin() const
{
	return _origin;
}

const Tuple& Ray::direction() const
{
	return _direction;
}

const Tuple Ray::position(float time) const
{
	return _origin + _direction * time;
}

const Ray Ray::transform(const Matrix& m) const
{
	return { m * _origin, m * _direction };
}

optional<Intersections> Ray::intersect(const ShapePtr& sph) const
{
	Matrix sphereTransform = sph->transform();
	Matrix invSphereTransform = sphereTransform.inverse();
	Ray transformedRay = transform(invSphereTransform);
	return sph->localIntersection(transformedRay);
}
