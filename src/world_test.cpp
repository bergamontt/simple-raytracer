#include "gtest/gtest.h"
#include "transformation.h"
#include "ray.h"
#include "world.h"
#include "shapes/plane.h"
#include "patterns/solid.h"
#include "patterns/stripe.h"

using namespace std;

TEST(WorldTest, IntersectWorld)
{
	World w = World::defaultWorld();
	Ray r(createPoint(0, 0, -5), createVector(0, 0, 1));
	optional<Intersections> xs = w.intersect(r);
	ASSERT_TRUE(xs.has_value());
	Intersections intrs = xs.value();
	ASSERT_FLOAT_EQ(intrs.get(0).time(), 4.0f);
	ASSERT_FLOAT_EQ(intrs.get(1).time(), 4.5f);
	ASSERT_FLOAT_EQ(intrs.get(2).time(), 5.5f);
	ASSERT_FLOAT_EQ(intrs.get(3).time(), 6.0f);
}

TEST(WorldTest, ShadingIntersectionOutside)
{
	World w = World::defaultWorld();
	Ray r(createPoint(0, 0, -5), createVector(0, 0, 1));
	auto& s = w.getObject(0);
	optional<Intersections> xs = r.intersect(s);
	Intersections intrs = xs.value();
	Intersection i = intrs.get(0);
	Computations comp(i, r);
	Color c = w.shadeHit(comp);
	ASSERT_EQ(c, createColor(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadingIntersectionInside)
{
	World w = World::defaultWorld();
	w.setLight({createPoint(0, 0.25, 0), createColor(1, 1, 1)});
	Ray r(createPoint(0, 0, 0), createVector(0, 0, 1));
	auto& s = w.getObject(1);
	optional<Intersections> xs = r.intersect(s);
	Intersections intrs = xs.value();
	Intersection i = intrs.get(1);
	Computations comp(i, r);
	Color c = w.shadeHit(comp);
	ASSERT_EQ(c, createColor(0.90498, 0.90498, 0.90498));
}

TEST(WorldTest, ColorWhenARayMisses)
{
	World w = World::defaultWorld();
	Ray r(createPoint(0, 0, -5), createVector(0, 1, 0));
	Color res = w.colorAt(r);
	ASSERT_EQ(res, createColor(0, 0, 0));
}

TEST(WorldTest, ColorWhenARayHits)
{
	World w = World::defaultWorld();
	Ray r(createPoint(0, 0, -5), createVector(0, 0, 1));
	Color res = w.colorAt(r);
	ASSERT_EQ(res, createColor(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColorWhithIntersectionBehindTheRay)
{
	World w = World::defaultWorld();

	auto& outer = w.getChangeableObject(0);
	Material outerm = outer->material();
	outerm.ambient = 1.0f;
	outer->setMaterial(outerm);

	auto& inner = w.getChangeableObject(1);
	Material innerm = inner->material();
	innerm.ambient = 1.0f;
	inner->setMaterial(innerm);

	Ray r(createPoint(0, 0, 0.75), createVector(0, 0, -1));

	Color res = w.colorAt(r);
	ASSERT_EQ(res, innerm.color);
}

TEST(WorldTest, ShadowedArea1)
{
	World w = World::defaultWorld();
	Tuple point = createPoint(0, 10, 0);
	ASSERT_FALSE(w.isShadowed(point));
}

TEST(WorldTest, ShadowedArea2)
{
	World w = World::defaultWorld();
	Tuple point = createPoint(10, -10, 10);
	ASSERT_TRUE(w.isShadowed(point));
}

TEST(WorldTest, ShadowedArea3)
{
	World w = World::defaultWorld();
	Tuple point = createPoint(-20, 20, -20);
	ASSERT_FALSE(w.isShadowed(point));
}

TEST(WorldTest, ShadowedArea4)
{
	World w = World::defaultWorld();
	Tuple point = createPoint(-2, 2, -2);
	ASSERT_FALSE(w.isShadowed(point));
}

TEST(WorldTest, ShadeHitInShadow)
{
	World w;
	w.setLight({ createPoint(0, 0, -10), createColor(1, 1, 1) });
	
	auto s1 = make_shared<Sphere>();
	w.addObject(s1);

	auto s2 = make_shared<Sphere>();
	s2->setTransform(translation(0, 0, 10));
	w.addObject(s2);

	Ray ray(createPoint(0, 0, 5), createVector(0, 0, 1));
	optional<Intersections> xs = ray.intersect(s2);
	Intersections intersections = xs.value();
	Intersection i = intersections.get(0);

	Computations comp(i, ray);
	Color color = w.shadeHit(comp);
	ASSERT_EQ(color, createColor(0.1, 0.1, 0.1));
}

TEST(WorldTest, ReflectedColor1)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, 0), createVector(0, 0, 1));
	auto& shape2 = w.getChangeableObject(1);
	Material m = shape2->material();
	m.ambient = 1;
	shape2->setMaterial(m);
	optional<Intersections> posIntr = ray.intersect(shape2);
	Intersections intr = posIntr.value();

	Computations comp(intr.get(0), ray);
	Color res = w.reflectedColor(comp);

	ASSERT_EQ(res, BLACK);
}

TEST(WorldTest, ReflectedColor2)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, -3), createVector(0, -sqrt(2) / 2, sqrt(2) / 2));
	
	Plane p;
	Material pm = p.material();
	pm.reflective = 0.5f;
	p.setMaterial(pm);
	p.setTransform(translation(0, -1, 0));
	auto shape = make_shared<Plane>(p);


	optional<Intersections> posIntr = ray.intersect(shape);
	Intersections intr = posIntr.value();

	Computations comp(intr.get(0), ray);
	Color res = w.reflectedColor(comp);

	ASSERT_EQ(res, createColor(0.19032, 0.2379, 0.14274));
}

TEST(WorldTest, ReflectedColor3)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, -3), createVector(0, -sqrt(2) / 2, sqrt(2) / 2));

	Plane p;
	Material pm = p.material();
	pm.reflective = 0.5f;
	p.setMaterial(pm);
	p.setTransform(translation(0, -1, 0));
	auto shape = make_shared<Plane>(p);


	optional<Intersections> posIntr = ray.intersect(shape);
	Intersections intr = posIntr.value();

	Computations comp(intr.get(0), ray);
	Color res = w.shadeHit(comp);

	ASSERT_EQ(res, createColor(0.87677, 0.92436, 0.82918));
}

TEST(WorldTest, RefractedColorWithOpaqueSurface)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, -5), createVector(0, 0, 1));
	ShapePtr& obj = w.getChangeableObject(0);
	optional<Intersections> posXs = ray.intersect(obj);
	Intersections xs = posXs.value();

	Computations comp(xs.get(0), ray, xs);
	Color refracted = w.refractedColor(comp);
	
	ASSERT_EQ(refracted, BLACK);
}

TEST(WorldTest, RefractedMaximumDepth)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, -5), createVector(0, 0, 1));
	ShapePtr& obj = w.getChangeableObject(0);
	obj->material().transparency = 1.0f;
	obj->material().reflactiveIndex = 1.5f;

	optional<Intersections> posXs = ray.intersect(obj);
	Intersections xs = posXs.value();

	Computations comp(xs.get(0), ray, xs);
	Color refracted = w.refractedColor(comp, 0);

	ASSERT_EQ(refracted, BLACK);
}

TEST(WorldTest, TotalInternalReflection)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, sqrt(2) / 2), createVector(0, 1, 0));
	
	ShapePtr& obj = w.getChangeableObject(0);
	obj->material().transparency = 1.0f;
	obj->material().reflactiveIndex = 1.5f;

	optional<Intersections> posXs = ray.intersect(obj);
	Intersections xs = posXs.value();

	Computations comp(xs.get(1), ray, xs);
	Color refracted = w.refractedColor(comp, 5);

	ASSERT_EQ(refracted, BLACK);
}

class Dummy : public Pattern
{
public:

	const Color colorAt(const Tuple& object_point) const
	{
		return Color(object_point._x, object_point._y, object_point._z);
	}

};

TEST(WorldTest, RefractedColor1)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, 0.1), createVector(0, 1, 0));

	ShapePtr& obj = w.getChangeableObject(0);
	obj->material().ambient = 1.0f;
	Solid white(WHITE);
	Solid black(BLACK);
	Stripe pattern(&white, &black);
	obj->material().pattern = new Dummy();

	ShapePtr& obj1 = w.getChangeableObject(1);
	obj1->material().transparency = 1.0f;
	obj1->material().reflactiveIndex = 1.5f;

	optional<Intersections> posXs = w.intersect(ray);
	Intersections xs = posXs.value();

	Computations comp(xs.get(2), ray, xs);
	Color refracted = w.refractedColor(comp, 5);

	ASSERT_EQ(refracted, createColor(0, 0.99888, 0.04725));
}

TEST(WorldTest, RefractedShadeHit)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, -3), createVector(0, - sqrt(2) / 2, sqrt(2) / 2));
	
	auto floor = make_shared<Plane>();
	floor->setTransform(translation(0, -1, 0));
	floor->material().transparency = 0.5f;
	floor->material().reflactiveIndex = 1.5f;

	w.addObject(floor);

	auto ball = make_shared<Sphere>();
	ball->material().color = RED;
	ball->material().ambient = 0.5f;
	ball->setTransform(translation(0, -3.5, -0.5));

	w.addObject(ball);

	optional<Intersections> posXs = ray.intersect(floor);
	Intersections xs = posXs.value();
	Computations comp(xs.get(0), ray, xs);

	Color res = w.shadeHit(comp, 5);
	ASSERT_EQ(res, createColor(0.93642, 0.68642, 0.68642));
}

TEST(WorldTest, ShadeHitWithSchlick)
{
	World w = World::defaultWorld();
	Ray ray(createPoint(0, 0, -3), createVector(0, -sqrt(2) / 2, sqrt(2) / 2));

	auto floor = make_shared<Plane>();
	floor->setTransform(translation(0, -1, 0));
	floor->material().transparency = 0.5f;
	floor->material().reflective = 0.5f;
	floor->material().reflactiveIndex = 1.5f;

	w.addObject(floor);

	auto ball = make_shared<Sphere>();
	ball->material().color = RED;
	ball->material().ambient = 0.5f;
	ball->setTransform(translation(0, -3.5, -0.5));

	w.addObject(ball);

	optional<Intersections> posXs = ray.intersect(floor);
	Intersections xs = posXs.value();
	Computations comp(xs.get(0), ray, xs);

	Color res = w.shadeHit(comp, 5);
	ASSERT_EQ(res, createColor(00.93391, 0.69643, 0.69243));
}