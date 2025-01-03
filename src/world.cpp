#include "world.h"
#include "transformation.h"

optional<Intersections> World::intersect(const Ray& ray)
{
	Intersections globalIntersections;
	for (auto& object : _objects)
	{
		optional<Intersections> intrs = ray.intersect(object);
		if (intrs.has_value())
		{
			Intersections xs = intrs.value();
			globalIntersections.merge(xs);
		}
			
	}
	return globalIntersections;
}

void World::addObject(const Sphere& sphere)
{
	_objects.push_back(sphere);
}

void World::setLight(const Light& light)
{
	_light = light;
}

void World::clearAllObjects()
{
	_objects.clear();
}

const Light World::light() const
{
	return _light;
}

const World World::defaultWorld()
{
	World world;
	Material material = { createColor(0.8f, 1.0f, 0.6f),
						  0.7f,
						  0.2f };
	Sphere s1, s2;
	s1.setMaterial(material);
	s2.setTransform(scaling(0.5f, 0.5f, 0.5f));
	world.addObject(s1);
	world.addObject(s2);
	return world;
}