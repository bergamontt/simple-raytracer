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

	const Color colorAt(const Ray& ray, int remaining = DEPTH) const;
	const Color shadeHit(const Computations& comp, int remaining = DEPTH) const;
	const Color reflectedColor(const Computations& comp, int remaining = DEPTH) const;
	
	bool isShadowed(const Tuple& point) const;

	optional<Intersections> intersect(const Ray& ray) const;

	void addObject(const ShapePtr& sphere);
	
	const Light& light() const;
	const ShapePtr& getObject(int index) const;
	ShapePtr& getChangeableObject(int index);

	void setLight(const Light& light);

	static const World defaultWorld();
	static const int DEPTH{ 4 };

private:

	vector<ShapePtr> _objects;
	Light _light;

};