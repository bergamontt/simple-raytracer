#pragma once
#include "shapes/sphere.h"
#include "const_colors.h"
#include "intersections.h"
#include "light.h"
#include "ray.h"
#include <vector>

using namespace std;

class World
{
public:

	World()
		: _light{createPoint(-10, 10, 10), WHITE}
	{}

	optional<Intersections> intersect(const Ray& ray);

	void addObject(const Sphere& sphere);
	void setLight(const Light& light);

	void clearAllObjects();

	const Light light() const;

	static const World defaultWorld();

private:

	vector<Sphere> _objects;
	Light _light;

};

