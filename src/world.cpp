#include "world.h"
#include "transformation.h"

const Color World::colorAt(const Ray& ray) const
{
	optional<Intersections> possibleIntersections = intersect(ray);
	if (!possibleIntersections.has_value())
		return BLACK;
	
	Intersections intersections = possibleIntersections.value();
	optional<Intersection> possibleHit = intersections.hit();
	if (!possibleHit.has_value())
		return BLACK;

	Intersection hit = possibleHit.value();
	Computations computations(hit, ray);
	return shadeHit(computations);
}

const Color World::shadeHit(const Computations& comp) const
{
	return lightning(comp.object()->material(), _light,
					 comp.point(),
					 comp.eyeVector(), comp.normalVector(),
					 isShadowed(comp.overPoint()));
}

optional<Intersections> World::intersect(const Ray& ray) const
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

bool World::isShadowed(const Tuple& point) const
{
	Tuple vector = _light.position() - point;
	float distance = magnitude(vector);
	Tuple direction = normalize(vector);

	Ray ray(point, direction);
	optional<Intersections> possibleIntersections = intersect(ray);
	if (!possibleIntersections.has_value())
		return false;
	
	Intersections intersections = possibleIntersections.value();
	optional<Intersection> possibleHit = intersections.hit();
	if (!possibleHit.has_value())
		return false;

	Intersection hit = possibleHit.value();
	return hit.time() < distance;
}

void World::addObject(const ShapePtr& sphere)
{
	_objects.push_back(sphere);
}

const ShapePtr& World::getObject(int index) const
{
	return _objects.at(index);
}

ShapePtr& World::getChangeableObject(int index)
{
	return _objects.at(index);
}

void World::setLight(const Light& light)
{
	_light = light;
}

const Light& World::light() const
{
	return _light;
}

const World World::defaultWorld()
{
	World world;
	Material material = { createColor(0.8f, 1.0f, 0.6f),
						  0.1f,
						  0.7f,
						  0.2f,
						  200.0f };
	auto s1 = make_shared<Sphere>();
	auto s2 = make_shared<Sphere>();
	s1->setMaterial(material);
	s2->setTransform(scaling(0.5f, 0.5f, 0.5f));
	world.addObject(s1);
	world.addObject(s2);
	return world;
}