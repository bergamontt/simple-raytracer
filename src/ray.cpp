#include <cmath>
#include "ray.h"
#include "matrix.h"
#include "shapes/shape.h"

using namespace std;

const Tuple Ray::origin() const
{
	return _origin;
}

const Tuple Ray::direction() const
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

//optional<Intersections> Ray::intersect(const ShapeConstPtr& s) const
//{
//	Matrix sphereTransform = s->transform();
//	Matrix invSphereTransform = sphereTransform.inverse();
//	Ray transformedRay = transform(invSphereTransform);
//	Tuple sphereToRay = transformedRay._origin - s.origin();
//
//	float a = dot(transformedRay._direction, transformedRay._direction);
//	float b = 2 * dot(transformedRay._direction, sphereToRay);
//	float c = dot(sphereToRay, sphereToRay) - 1;
//	float discriminant = b * b - 4 * a * c;
//
//	if (discriminant < 0)
//		return {};
//
//	float t1 = (-b - sqrt(discriminant)) / (2 * a);
//	float t2 = (-b + sqrt(discriminant)) / (2 * a);
//
//	Intersections intersections;
//
//	if (t1 > t2)
//	{
//		intersections.add({ t2 , s });
//		intersections.add({ t1 , s });
//	}
//	else {
//		intersections.add({ t1 , s });
//		intersections.add({ t2 , s });
//	}
//
//	return intersections;
//}