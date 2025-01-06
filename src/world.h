#pragma once
#include "computations.h"
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
		: _light{createPoint(-10, 10, -10), WHITE}
	{}

	const Color colorAt(const Ray& ray) const;
	const Color shadeHit(const Computations& comp) const;
	optional<Intersections> intersect(const Ray& ray) const;

	bool isShadowed(const Tuple& point) const;

	void addObject(const Sphere& sphere);
	const Sphere getObject(int index) const;
	Sphere& getChangeableObject(int index);

	const Light light() const;
	void setLight(const Light& light);

	static const World defaultWorld();

private:

	vector<Sphere> _objects;
	Light _light;

};

