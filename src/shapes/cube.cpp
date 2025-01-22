#include "cube.h"

optional<Intersections> Cube::localIntersection(const Ray& ray) const
{
	const Tuple& origin = ray.origin();
	const Tuple& direction = ray.direction();

	pair<float, float> xt = checkAxis(origin._x, direction._x);
	pair<float, float> yt = checkAxis(origin._y, direction._y);
	pair<float, float> zt = checkAxis(origin._z, direction._z);

	float tmin = fmax(xt.first, fmax(yt.first, zt.first));
	float tmax = fmin(xt.second, fmin(yt.second, zt.second));

	if (tmin > tmax) return {};

	Intersections xs;
	xs.add({tmin, shared_from_this() });
	xs.add({tmax, shared_from_this() });

	return xs;
}

const pair<float, float> Cube::checkAxis(float origin, float direction) const
{
	float tminNumerator = -1.0f - origin;
	float tmaxNumerator = 1.0f - origin;

	float tmin = tminNumerator * INFINITY;
	float tmax = tmaxNumerator * INFINITY;

	if (fabs(direction) >= EPSILON)
	{
		tmin = tminNumerator / direction;
		tmax = tmaxNumerator / direction;
	}
		
	if (tmin > tmax)
		swap(tmin, tmax);

	return { tmin, tmax };
}

const Tuple Cube::localNormal(const Tuple& point) const
{
	float maxc = fmax(fabs(point._x), fmax(fabs(point._y), fabs(point._z)));
	
	if (equalDouble(fabs(point._x), maxc))
		return createVector(point._x, 0.0f, 0.0f);
	if (equalDouble(fabs(point._y), maxc))
		return createVector(0.0f, point._y, 0.0f);

	return createVector(0.0f, 0.0f, point._z);;
}

