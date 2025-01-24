#include "cylinder.h"

float Cylinder::minimum() const
{
	return _minimum;
}

float Cylinder::maximum() const
{
	return _maximum;
}

bool Cylinder::capped() const
{
	return _capped;
}

void Cylinder::setMinimum(const float min)
{
	if (min > _maximum)
		return;
	_minimum = min;
}

void Cylinder::setMaximum(const float max)
{
	if (max < _minimum)
		return;
	_maximum = max;
}

void Cylinder::setCapped(const bool capped)
{
	_capped = capped;
}

optional<Intersections> Cylinder::localIntersection(const Ray& ray) const
{
	const Tuple& direction = ray.direction();
	float a = direction._x * direction._x +
			  direction._z * direction._z;
	
	if (equalDouble(a, 0.0f))
		return capIntersection(ray);

	const Tuple& origin = ray.origin();
	float b = 2 * origin._x * direction._x +
			  2 * origin._z * direction._z;
	float c = origin._x * origin._x +
			  origin._z * origin._z - 1.0f;

	float disc = b * b - 4 * a * c;
	if (disc < 0.0f)
		return capIntersection(ray);

	float t0 = (-b - sqrt(disc)) / (2.0f * a);
	float t1 = (-b + sqrt(disc)) / (2.0f * a);
	if (t0 > t1)
		swap(t0, t1);

	Intersections intersections;

	float y0 = origin._y + t0 * direction._y;
	if (y0 > minimum() && y0 < maximum())
		intersections.add({ t0, shared_from_this()});
	
	float y1 = origin._y + t1 * direction._y;
	if (y1 > minimum() && y1 < maximum())
		intersections.add({ t1, shared_from_this() });
	
	optional<Intersections> posCapIntersections = capIntersection(ray);
	if (posCapIntersections.has_value())
	{
		Intersections& capIntersections = posCapIntersections.value();
		intersections.merge(capIntersections);
	}

	if (intersections.size() == 0)
		return {};
	return intersections;
}

bool Cylinder::hitsCap(const Ray& ray, const float time) const
{
	const Tuple& direction = ray.direction();
	const Tuple& origin = ray.origin();

	float x = origin._x + time * direction._x;
	float z = origin._z + time * direction._z;
	
	return (x * x + z * z) <= 1.0f - EPSILON;
}

optional<Intersections> Cylinder::capIntersection(const Ray& ray) const
{
	const Tuple& direction = ray.direction();
	if (!capped() || equalDouble(direction._y, 0.0f))
		return {};

	const Tuple& origin = ray.origin();
	Intersections xs;

	float t0 = (minimum() - origin._y) / direction._y;
	if (hitsCap(ray, t0))
		xs.add({ t0, shared_from_this()} );

	float t1 = (maximum() - origin._y) / direction._y;
	if (hitsCap(ray, t1))
		xs.add({ t1, shared_from_this() });

	if (xs.size() == 0)
		return {};
	return xs;
}

const Tuple Cylinder::localNormal(const Tuple& point) const
{
	float distance = point._x * point._x + point._z * point._z;
	
	if (distance <= 1.0f && point._y >= maximum() - EPSILON)
		return createVector(0, 1, 0);
	if (distance <= 1.0f && point._y <= minimum() + EPSILON)
		return createVector(0, -1, 0);

	return createVector(point._x, 0.0f, point._z);
}
