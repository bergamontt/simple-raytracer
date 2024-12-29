#include <cmath>
#include "ray.h"

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

vector<float> Ray::intersect(const Sphere& sph) const
{
	Tuple sphereToRay = _origin - createPoint(0, 0, 0);

	float a = dot(_direction, _direction);
	float b = 2 * dot(_direction, sphereToRay);
	float c = dot(sphereToRay, sphereToRay) - 1;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return vector<float>();

	float t1 = (-b - sqrt(discriminant)) / (2 * a);
	float t2 = (-b + sqrt(discriminant)) / (2 * a);

	vector<float> intersections;
	
	if (t1 > t2)
	{
		intersections.push_back(t2);
		intersections.push_back(t1);
	}
	else {
		intersections.push_back(t1);
		intersections.push_back(t2);
	}

	return intersections;
}
