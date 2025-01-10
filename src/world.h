#pragma once
#include "types.h"
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

	void addObject(const ShapePtr& sphere);
	const ShapePtr& getObject(int index) const;
	ShapePtr& getChangeableObject(int index);

	const Light& light() const;
	void setLight(const Light& light);

	static const World defaultWorld();

private:

	vector<ShapePtr> _objects;
	Light _light;

};