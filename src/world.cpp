#include "world.h"
#include "transformation.h"
#include "lightning.h"

const Color World::colorAt(const Ray& ray, int remaining) const
{
	optional<Intersections> possibleIntersections = intersect(ray);
	if (!possibleIntersections.has_value())
		return BLACK;
	
	Intersections intersections = possibleIntersections.value();
	optional<Intersection> possibleHit = intersections.hit();
	if (!possibleHit.has_value())
		return BLACK;

	Intersection hit = possibleHit.value();
	Computations computations(hit, ray, intersections);
	return shadeHit(computations, remaining);
}

const Color World::shadeHit(const Computations& comp, int remaining) const
{
	const Material& objMaterial = comp.object()->material();
	Color surface = lightning(objMaterial,
					 comp.object(), _light,
					 comp.point(),
					 comp.eyeVector(), comp.normalVector(),
					 isShadowed(comp.overPoint()));
	Color reflected = reflectedColor(comp, remaining);
	Color refracted = refractedColor(comp, remaining);
	
	if (objMaterial.reflective > 0.0f && objMaterial.transparency > 0.0f)
	{
		float reflectance = comp.schlick();
		return surface + reflected * reflectance +
			refracted * (1.0f - reflectance);
	}

	return surface + reflected + refracted;
}

const Color World::reflectedColor(const Computations& comp, int remaining) const
{
	if (remaining <= 0)
		return BLACK;
	auto& object = comp.object();
	const Material& m = object->material();
	if (equalDouble(m.reflective, 0.0f))
		return BLACK;
	Ray reflectRay(comp.overPoint(), comp.reflectVector());
	Color color = colorAt(reflectRay, remaining - 1);
	return color * m.reflective;
}

const Color World::refractedColor(const Computations& comp, int remaining) const
{
	if (remaining == 0)
		return BLACK;
	const ShapeConstPtr& obj = comp.object();
	const Material& objMaterial = obj->material();
	if (equalDouble(objMaterial.transparency, 0.0f))
		return BLACK;

	float nRatio = comp.n1() / comp.n2();
	float cosI = dot(comp.eyeVector(), comp.normalVector());
	float sin2t = nRatio * nRatio * (1 - cosI * cosI);
	if (sin2t > 1.0f)
		return BLACK;

	float cosT = sqrt(1.0f - sin2t);
	Tuple direction = comp.normalVector() * (nRatio * cosI - cosT) -
					  comp.eyeVector() * nRatio;
	Ray refractRay(comp.underPoint(), direction);
	return colorAt(refractRay, remaining - 1) * objMaterial.transparency;
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